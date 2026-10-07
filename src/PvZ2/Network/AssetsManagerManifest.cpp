//
//  AssetsManagerManifest.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AssetsManagerManifest.h"
#include "SexyAppFramework/SexyAppBase.h"

/////////////// Lifecycle ///////////////

AssetsManagerManifest::~AssetsManagerManifest()
{
}

AssetsManagerManifest::Asset::Asset()
{
    md5 = "";
    path = "";
    compressed = false;
    downloadState = DownloadState::UNSTARTED;
}

AssetsManagerManifest::Asset::Asset(const Asset&) = default;

AssetsManagerManifest::Asset::~Asset() = default;

AssetsManagerManifest::AssetDiff::AssetDiff() = default;

AssetsManagerManifest::AssetDiff::AssetDiff(const AssetDiff&) = default;

AssetsManagerManifest::AssetDiff::~AssetDiff() = default;

AssetsManagerManifest::AssetsManagerManifest(const std::string& manifestUrl)
    : _versionLoaded(false)
    , _loaded(false)
    , _manifestRoot("")
    , _remoteManifestUrl("")
    , _remoteVersionUrl("")
    , _version("")
    , _totalfilesize(0)
    , _engineVer("")
{
    if (manifestUrl.size() > 0)
        parse(manifestUrl);
}

/////////////// Logic ///////////////

class StringHelper
{
public:
    static bool ReadJson(const std::string& i_json, Sexy::StructuredData* o_data);
};

typedef AssetsManagerManifest::Asset ManifestAsset;

typedef std::__umap_hashtable<std::string, ManifestAsset, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<const std::string, ManifestAsset> > > ManifestAssetTable;

typedef std::__umap_hashtable<std::string, std::string, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<const std::string, std::string> > > ManifestStringTable;

typedef std::pair<std::__detail::_Node_iterator<std::pair<const std::string, ManifestAsset>, false, true>, bool> ManifestAssetEmplaceResult;

typedef std::pair<std::__detail::_Node_iterator<std::pair<const std::string, std::string>, false, true>, bool> ManifestStringEmplaceResult;

ManifestAssetEmplaceResult ManifestAssetTable_MEmplace(ManifestAssetTable * table, const std::string & key, ManifestAsset & asset);

ManifestStringEmplaceResult ManifestStringTable_MEmplace(ManifestStringTable * table, std::string & key, std::string & value);

namespace std
{
template<> template<>
ManifestAssetEmplaceResult ManifestAssetTable::emplace<const std::string &, ManifestAsset &>(const std::string & key, ManifestAsset & asset)
{
    return ManifestAssetTable_MEmplace(this, std::forward<const std::string &>(key), std::forward<ManifestAsset &>(asset));
}
template<> template<>
ManifestStringEmplaceResult ManifestStringTable::emplace<std::string &, std::string &>(std::string & key, std::string & value)
{
    return ManifestStringTable_MEmplace(this, std::forward<std::string &>(key), std::forward<std::string &>(value));
}
}

void AssetsManagerManifest::prependSearchPaths()
{
}

bool AssetsManagerManifest::isVersionLoaded() const
{
    return _versionLoaded;
}

bool AssetsManagerManifest::isLoaded() const
{
    return _loaded;
}

const std::string& AssetsManagerManifest::getPackageUrl() const
{
    return _packageUrl;
}

const std::string& AssetsManagerManifest::getManifestFileUrl() const
{
    return _remoteManifestUrl;
}

const std::string& AssetsManagerManifest::getVersionFileUrl() const
{
    return _remoteVersionUrl;
}

const std::string& AssetsManagerManifest::getVersion() const
{
    return _version;
}

float AssetsManagerManifest::getTotalFileSize() const
{
    return _totalfilesize;
}

const std::vector<std::string>& AssetsManagerManifest::getGroups() const
{
    return _groups;
}

const std::unordered_map<std::string, std::string>& AssetsManagerManifest::getGroupVerions() const
{
    return _groupVer;
}

const std::string& AssetsManagerManifest::getGroupVersion(const std::string &group) const
{
    return _groupVer.at(group);
}

const std::unordered_map<std::string, AssetsManagerManifest::Asset>& AssetsManagerManifest::getAssets() const
{
    return _assets;
}

void AssetsManagerManifest::parseVersion(const std::string& versionUrl, const std::string& rsbVersion)
{
    loadJson(versionUrl);
    loadVersion(_json, rsbVersion);
}

void AssetsManagerManifest::clear()
{
    if (_versionLoaded || _loaded)
    {
    _groups.clear();
    _groupVer.clear();
    _remoteManifestUrl = "";
    _remoteVersionUrl = "";
    _version = "";
    _engineVer = "";
    _versionLoaded = false;
    }
    if (_loaded)
    {
    _assets.clear();
    _searchPaths.clear();
    _loaded = false;
    }
}

void AssetsManagerManifest::saveToFile(const std::string &filepath)
{
    Sexy::Buffer buffer;
    _json.WriteToBuffer(&buffer);
    Sexy::gSexyAppBase->WriteBufferToFile(filepath, &buffer);
}

void AssetsManagerManifest::parse(const std::string& manifestUrl)
{
    loadJson(manifestUrl);
    size_t found = manifestUrl.find_last_of("/\\");
    if (found != std::string::npos)
    {
        _manifestRoot = manifestUrl.substr(0, found + 1);
    }
    loadManifest(_json);
}

int AssetsManagerManifest::getVersionToInt(std::string i_version)
{
    if (i_version == "")
        return 0;
    int result = 0;
    Sexy::StringToInt(i_version, &result);
    return result;
}

AssetsManagerManifest::Asset& AssetsManagerManifest::Asset::operator=(const Asset&) = default;

void AssetsManagerManifest::setAssetDownloadState(const std::string &key, const DownloadState &state)
{
    auto it = _assets.find(key);
    if (it != _assets.end())
    {
        it->second.downloadState = state;
        const Sexy::StructuredData::Value *assets = _json.ValueForPath("$.assets");
        if (assets != nullptr && assets->IsObject())
        {
            for (const Sexy::StructuredData::Value *child = assets->ChildrenBegin(); child != assets->ChildrenEnd(); child = child->Next())
            {
                if (child != nullptr && child->IsObject())
                {
                    if (key.compare(child->Name()) == 0)
                    {
                        _json.SetInteger(child, "downloadState", (int)state);
                        break;
                    }
                }
            }
        }
    }
}

AssetsManagerManifest::Asset AssetsManagerManifest::parseAsset(const std::string &path, const Sexy::StructuredData::Value &json)
{
    Asset asset;
    asset.path = path;
    asset.md5 = "";
    asset.compressed = false;
    asset.downloadState = DownloadState::UNSTARTED;
    for (const Sexy::StructuredData::Value *it = json.ChildrenBegin(); it != json.ChildrenEnd(); it = it->Next())
    {
        if (it != nullptr)
        {
            std::string key = it->Name();
            if (key == "md5" && it->IsString())
                asset.md5 = it->GetString();
            else if (key == "path" && it->IsString())
                asset.path = it->GetString();
            else if (key == "compressed" && it->IsBoolean())
                asset.compressed = it->GetBoolean();
            else if (key == "downloadState" && it->IsInteger())
                asset.downloadState = (DownloadState)it->GetInteger();
        }
    }
    return asset;
}

void AssetsManagerManifest::loadManifest(const Sexy::StructuredData &json)
{
    loadVersion(json, std::string("0"));
    std::string packageUrl(json.StringForPath("$.packageUrl", ""), std::allocator<char>());
    if (packageUrl.length() != 0)
    {
        _packageUrl = packageUrl;
        size_t len = _packageUrl.length();
        if (len != 0 && _packageUrl[len - 1] != '/')
            _packageUrl += "/";
    }
    const Sexy::StructuredData::Value *assets = json.ValueForPath("$.assets");
    if (assets != nullptr && assets->IsObject())
    {
        for (const Sexy::StructuredData::Value *it = assets->ChildrenBegin(); it != assets->ChildrenEnd(); it = it->Next())
        {
            if (it != nullptr && it->IsObject())
            {
                const std::string key(it->Name(), std::allocator<char>());
                Asset asset = parseAsset(key, *it);
                _assets.emplace(key, asset);
                
            }
        }
    }
    _loaded = true;
}

void AssetsManagerManifest::loadVersion(const Sexy::StructuredData &json, const std::string &rsbVersion)
{
    std::string remoteManifestUrl(json.StringForPath("$.remoteManifestUrl", ""), std::allocator<char>());
    if (remoteManifestUrl.length() != 0)
        _remoteManifestUrl = remoteManifestUrl;
    std::string remoteVersionUrl(json.StringForPath("$.remoteVersionUrl", ""), std::allocator<char>());
    if (remoteVersionUrl.length() != 0)
        _remoteVersionUrl = remoteVersionUrl;
    if (rsbVersion == "0")
    {
        std::string version(json.StringForPath("$.version", ""), std::allocator<char>());
        if (version.length() != 0)
            _version = version;
    }
    else
    {
        _version = rsbVersion;
    }
    const Sexy::StructuredData::Value *groups = json.ValueForPath("$.groupVersions");
    if (groups != nullptr && groups->IsObject())
    {
        for (const Sexy::StructuredData::Value *it = groups->ChildrenBegin(); it != groups->ChildrenEnd(); it = it->Next())
        {
            if (it != nullptr)
            {
                std::string name(it->Name(), std::allocator<char>());
                std::string version("0");
                if (it->IsString())
                    version = it->GetString();
                _groups.push_back(name);
                _groupVer.emplace(name, version);
            }
        }
    }
    std::string engineVersion(json.StringForPath("$.engineVersion", ""), std::allocator<char>());
    if (engineVersion.length() != 0)
        _engineVer = engineVersion;
    _totalfilesize = json.NumberForPath("$.totalfilesize", 0.0);
    _versionLoaded = true;
}

std::vector<std::string> AssetsManagerManifest::getSearchPaths() const
{
    std::vector<std::string> paths;
    paths.push_back(_manifestRoot);
    for (int i = (int)_searchPaths.size() - 1; i >= 0; i--)
    {
        std::string path = _searchPaths[i];
        if (path.size() != 0 && path[path.size() - 1] != '/')
            path += "/";
        path = _manifestRoot + path;
        paths.push_back(path);
    }
    return paths;
}

void AssetsManagerManifest::loadJson(const std::string& url)
{
    clear();
    std::string content;
    if (Sexy::gSexyAppBase->FileExists(url))
    {
        Sexy::Buffer buffer;
        Sexy::Buffer header;
        if (Sexy::gSexyAppBase->ReadBufferFromFile(url, &buffer, true) && Sexy::gSexyAppBase->ReadBufferFromFile(url, &header, true))
        {
            bool ok;
            if (header.ReadInt() == 0x50435344)
            {
                ok = _json.ReadFromBuffer(&buffer);
            }
            else
            {
                content.insert(content.end(), (char*)buffer.GetDataPtr(), (char*)buffer.GetDataPtr() + buffer.GetDataLen());
                ok = content.size() != 0 && StringHelper::ReadJson(content, &_json);
            }
            if (!ok)
                Sexy::OutputDebugStrF("Fail to retrieve local file content: %s\n", url.c_str());
        }
    }
}

bool AssetsManagerManifest::versionEquals(const AssetsManagerManifest *b) const
{
    if (_version != b->getVersion())
        return false;
    {
        std::vector<std::string> bGroups = b->getGroups();
        std::unordered_map<std::string, std::string> bGroupVer = b->getGroupVerions();
        if (bGroups.size() != _groups.size())
            return false;
        for (unsigned int i = 0; i < _groups.size(); i++)
        {
            std::string group = _groups[i];
            if (group != bGroups[i])
                return false;
            if (_groupVer.at(group) != bGroupVer.at(group))
                return false;
        }
    }
    return true;
}

void AssetsManagerManifest::genResumeAssetsList(DownloadUnits *units, const std::string& i_cdnUrl, const std::string& rsbVersion) const
{
    for (std::unordered_map<std::string, Asset>::const_iterator it = _assets.begin(); it != _assets.end(); ++it)
    {
        Asset asset = it->second;
        if (asset.downloadState != DownloadState::SUCCESSED)
        {
            DownloadUnit unit;
            unit.customId = it->first;
            unit.srcUrl = i_cdnUrl + rsbVersion + "/" + _packageUrl + asset.path;
            unit.storagePath = _manifestRoot + asset.path;
            units->emplace(unit.customId, unit);
        }
    }
}

std::unordered_map<std::string, AssetsManagerManifest::AssetDiff> AssetsManagerManifest::genDiff(const AssetsManagerManifest *b) const
{
    typedef std::pair<const std::string, Asset> Entry;
    std::unordered_map<std::string, AssetDiff> diff;
    const std::unordered_map<std::string, Asset>& bAssets = b->getAssets();
    std::unordered_map<std::string, Asset>::const_iterator found;
    std::unordered_map<std::string, Asset>::const_iterator it;
    for (it = _assets.begin(); it != _assets.end(); ++it)
    {
        const Entry *entry = it.operator->();
        const Asset& asset = entry->second;
        found = bAssets.find(entry->first);
        if (found == bAssets.end())
        {
            AssetDiff d;
            d.asset = asset;
            d.type = DiffType::DELETED;
            diff.emplace(entry->first, d);
        }
        else
        {
            const Asset& other = found->second;
            if (asset.md5 != other.md5)
            {
                AssetDiff d;
                d.asset = other;
                d.type = DiffType::MODIFIED;
                diff.emplace(entry->first, d);
            }
        }
    }
    for (it = bAssets.begin(); it != bAssets.end(); ++it)
    {
        const Entry *entry = it.operator->();
        found = _assets.find(entry->first);
        if (found == _assets.end())
        {
            AssetDiff d;
            d.asset = entry->second;
            d.type = DiffType::ADDED;
            diff.emplace(entry->first, d);
        }
    }
    return diff;
}
