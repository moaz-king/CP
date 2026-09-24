import json
from pathlib import Path

templates_dir = Path("templates")
output_file = Path("cpp.json")

snippets = {}

for file in templates_dir.glob("*.cpp"):
  text = file.read_text(encoding = "utf-8")
  body = text.splitlines()
  name = file.stem
  snippets[name] = {
    "prefix": name,
    "body": body,
  }

output_file.write_text(
  json.dumps(snippets, indent = 2),
  encoding = "utf-8"
)

print(f"Generated {output_file}")