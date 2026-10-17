"""Hook every libSrc.so function (>=64 B) 1000 at a time, one fresh game launch per batch; results in build/trace_all/ (resumable, trace_all.py [seconds_per_batch])."""
import json, os, re, subprocess, sys, time
import frida

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import config
from lib import pvzelf

PKG, N = 'com.popcap.pvz2cthdxy51', 1000
secs = int(sys.argv[1]) if len(sys.argv) > 1 else 45
OUT = os.path.join(config.BUILD, 'trace_all')
os.makedirs(OUT, exist_ok=True)
done_off = {int(m, 16) for m in re.findall(r'\[(0x[0-9a-f]+),', open(os.path.join(os.path.dirname(__file__), 'hook_all_boot.js'), encoding='utf-8').read())}
funcs = {}
for n, v, s, sh, t, b in pvzelf.Elf(config.TARGET_LIB).symbols_full():
    if t == 2 and sh and s >= 64 and v not in funcs and v not in done_off:
        funcs[v] = n
items = sorted(funcs.items())
batches = [items[i:i + N] for i in range(0, len(items), N)]
print(f'{len(items)} functions, {len(batches)} batches', flush=True)

JS = """
const OFFS = %s, C = {};
function go(base) { for (const o of OFFS) { try { Interceptor.attach(base.add(o), { onEnter() { C[o] = (C[o] || 0) + 1; } }); } catch (e) {} } send('hooked'); }
setInterval(() => send(JSON.stringify(C)), 3000);
const m = Process.findModuleByName('libSrc.so');
if (m) go(m.base); else { const ob = Process.attachModuleObserver({ onAdded(x) { if (x.name === 'libSrc.so') { ob.detach(); setTimeout(() => go(x.base), 0); } } }); }
"""

dev = frida.get_usb_device()
for i, b in enumerate(batches):
    path = os.path.join(OUT, f'batch_{i:03d}.json')
    if os.path.exists(path):
        continue
    subprocess.run(['adb', 'shell', 'am', 'force-stop', PKG], capture_output=True)
    time.sleep(2)
    last, state = {}, {'dead': False}
    pid = dev.spawn([PKG])
    ses = dev.attach(pid)
    ses.on('detached', lambda r, c: state.update(dead=True))
    def on_msg(m, d):
        p = m.get('payload')
        if m['type'] == 'send' and p and p.startswith('{'):
            last.clear(); last.update(json.loads(p))
    sc = ses.create_script(JS % json.dumps([v for v, _ in b]))
    sc.on('message', on_msg)
    sc.load(); dev.resume(pid)
    t0 = time.time()
    while not state['dead'] and time.time() - t0 < secs:
        time.sleep(1)
    names = dict(b)
    res = {names[int(o)]: c for o, c in last.items()}
    json.dump({'died': state['dead'], 'called': res}, open(path, 'w'))
    print(f'batch {i + 1}/{len(batches)}: {len(res)} called, died={state["dead"]}', flush=True)
    try: dev.kill(pid)
    except Exception: pass
subprocess.run(['adb', 'shell', 'am', 'force-stop', PKG], capture_output=True)
print('all batches done', flush=True)
