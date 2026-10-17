"""Spawn the game with hook_all_boot.js counting calls in-process; rewrites build/trace_live.txt every 2 s until Ctrl-C or the game dies."""
import os, time
import frida

H = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(H, '..', '..', 'build', 'trace_live.txt')
src = open(os.path.join(H, 'hook_all_boot.js'), encoding='utf-8').read()
src = src.replace("console.log('HIT ' + name);", "if (!(name in C)) { C[name] = 0; ORDER.push(name); } C[name]++;")
src = "const C = {}, ORDER = [];\nsetInterval(() => send(JSON.stringify(ORDER.map(n => [n, C[n]]))), 2000);\n" + src
dev = frida.get_usb_device()
pid = dev.spawn(['com.popcap.pvz2cthdxy51'])
ses = dev.attach(pid)
state = {'dead': False}
ses.on('detached', lambda r, c: state.update(dead=True))
def on_msg(m, d):
    if m['type'] == 'send' and m['payload'].startswith('['):
        import json
        rows = json.loads(m['payload'])
        with open(OUT, 'w') as f:
            f.write('\n'.join(f'{c}\t{n}' for n, c in rows))
sc = ses.create_script(src)
sc.on('message', on_msg)
sc.load()
dev.resume(pid)
while not state['dead']:
    time.sleep(1)
