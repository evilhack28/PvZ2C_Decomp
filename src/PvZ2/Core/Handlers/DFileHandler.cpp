//
//  DFileHandler.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"
#include "PvZ/DNode/DStream.h"
#include "PvZ/DNode/DStackAllocator.h"

/////////////// Lifecycle ///////////////

DFileHandler::DFileHandler()
    : m_bModify(false), m_bSercet(false), m_bWritable(true), m_bBuffer(false), m_sercetType(1)
{
}

DFileHandler::~DFileHandler()
{
}

bool DFileHandler::initWithString(const std::string& str, bool sercet)
{
    m_strName = str;
    m_bSercet = sercet;
    m_bWritable = false;
    m_bBuffer = true;
    return reload();
}

bool DFileHandler::initWithFile(const std::string& fileName, bool sercet)
{
    m_strName = fileName;
    m_bSercet = sercet;
    m_bWritable = false;
    m_bBuffer = false;
    return reload();
}

bool DFileHandler::initWithWritablePath(const std::string& fileName, bool sercet)
{
    m_strName = fileName;
    m_bSercet = sercet;
    m_bWritable = true;
    m_bBuffer = false;
    return reload();
}

/////////////// Accessors ///////////////

bool DFileHandler::isEmpty()
{
    return true;
}

bool DFileHandler::isModify()
{
    return m_bModify;
}

const std::string& DFileHandler::getFileName()
{
    return m_strName;
}

void DFileHandler::setSercetType(int type)
{
    m_sercetType = type;
}

/////////////// File ///////////////

bool DFileHandler::copyToFile(const std::string& fileName)
{
    DInputStream stream;
    bool ok;
    if (!m_bBuffer)
    {
        if (!m_bWritable)
            ok = stream.readFromFile(m_strName);
        else
            ok = stream.readFromWritabelPathFile(m_strName);
    }
    else
        ok = stream.readFromBuffer((const unsigned char*)m_strName.c_str(), m_strName.size());
    bool result = false;
    if (ok)
    {
        DWriteFile file;
        result = file.init(fileName.c_str(), false, true);
        if (!result)
            goto done;
        file.writeBytes(stream.getBuff(), stream.getLength());
    }
done:
    return result;
}

bool DFileHandler::read()
{
    DInputStream stream;
    bool ok;
    if (!m_bBuffer)
    {
        if (!m_bWritable)
            ok = stream.readFromFile(m_strName);
        else
            ok = stream.readFromWritabelPathFile(m_strName);
    }
    else
        ok = stream.readFromBuffer((const unsigned char*)m_strName.c_str(), m_strName.size());
    if (!ok)
        return false;
    size_t length = stream.getLength();
    if (length == 0)
        return false;
    unsigned char* buff = (unsigned char*)DStackAllocator::getInstance()->push(length + 2);
    stream.readBuffer(buff, length);
    unsigned char* body = buff;
    if (buff[0] == 'L' && buff[1] == 'o' && buff[2] == 'c' && buff[3] == 'k')
    {
        int skip = 0;
        if (buff[5] == '$')
        {
            if (buff[4] == '0')
            {
                m_sercetType = 0;
                skip = 6;
            }
            else
            {
                skip = 6;
                m_sercetType = 1;
            }
        }
        else if (buff[4] == '$')
        {
            m_sercetType = 0;
            skip = 5;
        }
        body = buff + skip;
        unsercet(body, length - skip, m_sercetType);
    }
    buff[length] = '\n';
    buff[length + 1] = 0;
    readBuff((const char*)body);
    DStackAllocator::getInstance()->pop();
    return true;
}

bool DFileHandler::writeToFile(const std::string& fileName, bool sercet, bool force)
{
    bool needWrite = m_bModify | force;
    if (needWrite)
    {
        DWriteFile file;
        if (!file.init(fileName.c_str(), false, force))
            return needWrite;
        DStreamBuffer stream(1024);
        m_strName = fileName;
        m_bBuffer = false;
        m_bModify = false;
        m_bWritable = true;
        m_bSercet = sercet;
        if (sercet)
        {
            DString header;
            header.format("Lock%d$", m_sercetType);
            file.writeBytes(header.c_str(), header.size());
        }
        writeBuff(stream);
        unsigned char* buff = (unsigned char*)stream.getBuff();
        size_t length = stream.getLength();
        if (m_bSercet)
        {
            if (m_sercetType == 0)
                length = (length + 15) & ~15UL;
            ::sercet(buff, length, m_sercetType);
        }
        file.writeBytes(buff, length);
    }
    return needWrite;
}

bool DFileHandler::reload()
{
    m_bModify = false;
    clear();
    return read();
}

bool DFileHandler::write()
{
    if (!m_bWritable)
        return false;
    return writeToFile(m_strName, m_bSercet, false);
}

bool DFileHandler::flush()
{
    return write();
}

void DFileHandler::close()
{
    write();
    clear();
}

void DFileHandler::removeAllItems()
{
    if (!isEmpty())
    {
        clear();
        m_bModify = true;
    }
}
