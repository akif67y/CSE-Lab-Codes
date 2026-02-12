import subprocess
import os
import sys

# Configuration
files = {
    "Chaining Method": "Chaining",        # Name of your cpp file (without .cpp)
    "Double Hashing": "DoubleHashing",    # Name of your cpp file
    "Custom Probing": "CustomProbing"     # Name of your cpp file
}

def compile_and_run(label, filename):
    exe_extension = ".exe" if os.name == 'nt' else ""
    executable = f"{filename}{exe_extension}"
    
    print(f"[*] Processing {label}...")

    # 1. Compile (assuming g++ is in your PATH)
    compile_cmd = ["g++", f"{filename}.cpp", "-o", filename]
    try:
        subprocess.run(compile_cmd, check=True)
    except subprocess.CalledProcessError:
        print(f"Error: Failed to compile {filename}.cpp")
        return None

    # 2. Run
    run_cmd = [f".\\{executable}"] if os.name == 'nt' else [f"./{executable}"]
    try:
        result = subprocess.run(run_cmd, capture_output=True, text=True, check=True)
    except subprocess.CalledProcessError:
        print(f"Error: Failed to run {executable}")
        return None

    # 3. Parse Output (Looking for the line starting with "CSV:")
    for line in result.stdout.splitlines():
        if line.startswith("CSV:"):
            # Format: CSV:col1,hits1,col2,hits2
            data = line.replace("CSV:", "").split(",")
            return {
                "col1": data[0],
                "hits1": float(data[1]),
                "col2": data[2],
                "hits2": float(data[3])
            }
    
    print(f"Error: Could not find 'CSV:' data line in output of {filename}")
    return None

# --- Main Execution ---
results = {}

print("--- Starting Simulation ---")
for label, filename in files.items():
    data = compile_and_run(label, filename)
    if data:
        results[label] = data
    else:
        # Fill with error placeholders if failed
        results[label] = {"col1": "ERR", "hits1": 0.0, "col2": "ERR", "hits2": 0.0}

print("\n\n")

# --- Generate Table ---
# Adjust widths to match the ASCII art style
w_label = 18
w_col = 22
w_hits = 15

# Top Border
print("-" * (w_label + 2 * (w_col + w_hits) + 5))

# Header Row 1
print(f"|{'':<{w_label}}|{'Hash1':^{w_col + w_hits + 1}}|{'Hash2':^{w_col + w_hits + 1}}|")

# Header Row 2
print(f"|{'':<{w_label}}|{'Number of Collisions':^{w_col}}|{'Average Hits':^{w_hits}}|{'Number of Collisions':^{w_col}}|{'Average Hits':^{w_hits}}|")

# Separator
print("-" * (w_label + 2 * (w_col + w_hits) + 5))

# Data Rows
for label in ["Chaining Method", "Double Hashing", "Custom Probing"]:
    r = results[label]
    
    # Format hits to 3 decimal places
    h1 = f"{r['hits1']:.3f}"
    h2 = f"{r['hits2']:.3f}"
    
    print(f"|{label:<{w_label}}|{r['col1']:^{w_col}}|{h1:^{w_hits}}|{r['col2']:^{w_col}}|{h2:^{w_hits}}|")
    
    # Row Separator
    print("-" * (w_label + 2 * (w_col + w_hits) + 5))

print("\nDone.")