import json
from pathlib import Path

templates_dir = Path("templates")
output_file = Path("cpp.json")

snippets = {}

for file in templates_dir.glob("*.cpp"):
    # Read the template
    text = file.read_text(encoding="utf-8")

    # VS Code snippet body is an array of lines
    body = text.splitlines()

    # Use filename as snippet name/prefix
    name = file.stem
    prefix = file.stem

    snippets[name] = {
        "prefix": prefix,
        "body": body,
        "description": f"{name}"
    }

output_file.write_text(
    json.dumps(snippets, indent=2),
    encoding="utf-8"
)

print(f"Generated {output_file}")