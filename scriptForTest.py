#!/usr/bin/python3
import random
import string
import os

COUNT_FILES = 10
DIR_NAME = "testDirectory"

suspicions = [
    "<script>evil_script()</script>",
    "rm -rf ~/Documents",
    "system(\"launchctl load /Library/LaunchAgents/com.malware.agent\")",
    "\n"
]

suspicions_count = [0] * 4

if not os.path.exists(DIR_NAME):
    os.makedirs(DIR_NAME)
for i in range(COUNT_FILES):
    index = random.randint(0, 3)
    suspicions_count[index] += 2
    f = open(f"{DIR_NAME}/fileTest{i}.txt", 'w')
    f.write(''.join(random.choices(string.ascii_uppercase + string.digits, k=random.randint(500000, 1000000))))
    f.write(suspicions[index])
    f.write(''.join(random.choices(string.ascii_uppercase + string.digits, k=random.randint(500000, 1000000))))
    f.write(suspicions[index])
    f.write(''.join(random.choices(string.ascii_uppercase + string.digits, k=random.randint(500000, 1000000))))
    f.close()

print(""
      f"Processed files: {COUNT_FILES}\n"
      f"JS detects: {suspicions_count[0]}\n"
      f"Unix detects: {suspicions_count[1]}\n"
      f"macOS detects: {suspicions_count[2]}"
      )
