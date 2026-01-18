import os
import subprocess

# --- CONFIGURATION ---
TEST_RANGE = range(1, 11)
ALGOS = {
    'p': {'name': "Prim", 'source': "2305006_prim.cpp", 'exe': "prim_runner", 'out_dir': "sampleio/prims"},
    'k': {'name': "Kruskal", 'source': "2305006_kruskal.cpp", 'exe': "kruskal_runner", 'out_dir': "sampleio/kruskals"}
}
# ---------------------

def parse_output(text):
    data = {'weight': None, 'edges': set()}
    for line in text.strip().splitlines():
        parts = line.split()
        if not parts: continue
        
        # Capture Weight
        if "Total weight" in line:
            try: data['weight'] = int(parts[-1])
            except: pass
            continue
            
        # Capture Edges (normalize 1-2 and 2-1)
        if len(parts) >= 2 and parts[0].isdigit() and parts[1].isdigit():
            u, v = int(parts[0]), int(parts[1])
            data['edges'].add(tuple(sorted((u, v))))
    return data

def run_tests():
    choice = input("Test [p] Prim or [k] Kruskal? ").lower().strip()
    if choice not in ALGOS: return print("Invalid choice")
    
    cfg = ALGOS[choice]
    # Compile
    if os.system(f"g++ {cfg['source']} -o {cfg['exe']}") != 0: return

    print(f"\n--- Testing {cfg['name']} ---")
    
    for i in TEST_RANGE:
        in_file = f"sampleio/input/test{i}.txt"
        exp_file = f"{cfg['out_dir']}/out{i}.txt"
        
        if not os.path.exists(in_file): continue
        
        # Run User Code
        cmd = f".{os.sep}{cfg['exe']}" 
        with open(in_file) as f: input_data = f.read()
        proc = subprocess.run(cmd, input=input_data, capture_output=True, text=True, shell=True)
        
        user = parse_output(proc.stdout)
        
        if os.path.exists(exp_file):
            with open(exp_file) as f: exp = parse_output(f.read())
            
            # CHECK 1: Total Weight (CRITICAL)
            if user['weight'] != exp['weight']:
                print(f"❌ Test {i}: FAILED (Weight Mismatch)")
                print(f"   Expected {exp['weight']}, Got {user['weight']}")
            
            # CHECK 2: Edges (WARNING ONLY)
            elif user['edges'] != exp['edges']:
                print(f"⚠️  Test {i}: PASSED (Weight Matches, Edges Differ)")
                print(f"   Note: This is acceptable for Test 2, 5, etc.")
            
            # PERFECT MATCH
            else:
                print(f"✅ Test {i}: PASSED (Exact Match)")
                
    # Cleanup
    try: os.remove(cfg['exe'] + (".exe" if os.name == 'nt' else ""))
    except: pass

if __name__ == "__main__":
    run_tests()