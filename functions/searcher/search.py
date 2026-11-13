from pathlib import Path
import sys
import json

## C++ & Python are silly and don't like importing things properly
projectRoot = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(projectRoot))

from functions.python.readCSV import readCSV
from functions.python.findAudioURL import findAudioURL

def main(location):
  dictionaryList = readCSV(location=location)

  for dictItem in dictionaryList:
    dictItem = {key: dictItem[key] for key in ["Song", "Artist", "Duration", "Album", "Spotify Track Id"]} # Only keys we need
    findAudioURL(songData=dictItem)
    print(json.dumps(dictItem), flush=1)


if __name__ == "__main__":
  if len(sys.argv) > 1:
    main(sys.argv[1])
  else:
    print("No location provided")