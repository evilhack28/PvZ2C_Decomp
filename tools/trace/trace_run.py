"""Spawn the game with hook_all_boot.js and write every HIT to build/trace.txt until ShowMainMenu (trace_run.py [max_seconds])."""
import os, sys, time
import frida

H = os.path.dirname(os.path.abspath(__file__))
secs = int(sys.argv[1]) if len(sys.argv) > 1 else 150
dev = frida.get_usb_device()
pid = dev.spawn(['com.popcap.pvz2cthdxy51'])
ses = dev.attach(pid)
out = open(os.path.join(H, '..', '..', 'build', 'trace.txt'), 'w')
done = []
def on_msg(m, d):
    t = m.get('payload') if m['type'] == 'send' else m.get('description')
    if t:
        out.write(t + '\n')
        if 'ShowMainMenu' in t:
            done.append(1)
ses.on('detached', lambda r, c: (out.write('[detached] %s\n' % r), done.append(1)))
sc = ses.create_script(open(os.path.join(H, 'hook_all_boot.js'), encoding='utf-8').read().replace('console.log(', 'send('))
sc.on('message', on_msg)
sc.load()
dev.resume(pid)
t0 = time.time()
while not done and time.time() - t0 < secs:
    time.sleep(0.5)
out.close()
try: dev.kill(pid)
except Exception: pass
