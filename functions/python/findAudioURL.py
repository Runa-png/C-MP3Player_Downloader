from yt_dlp import YoutubeDL
from fuzzywuzzy import fuzz 
from math import floor

def findAudioURL(songData):
  options = {
    "quiet": True,
    "nowarnings": True,
    "noplaylist": True,
    "extract_flat": True
  }

  if not (songData["Song"] and songData["Artist"]): # The only columns needed for searching
    return {"status": False, "data": "Missing Data"}
  
  artistList = songData["Artist"].split(",")
  
  with YoutubeDL(options) as ydl:
    # Iterate over each artist
    accuracyList = []
    for artist in artistList:
      query = songData["Song"] + " " + artist

      results = ydl.extract_info(
        f"ytsearch5:{query}",
        download = False
      )
      audio = results.get("entries", [])
    
      # Calculate the accuracy of the result
      for instance in audio:
        resultName = instance.get("title")
        resultArtist = instance.get("uploader")
        resultID = instance.get("id")

        nameRatio = fuzz.ratio(resultName, songData["Song"])
        artistRatio = fuzz.ratio(resultArtist, artist)
        totalRatio = floor((nameRatio + artistRatio) / 2)

        accuracyList.append({"id": resultID, "ratio": totalRatio, "uploader": resultArtist})
      
    # Find the highest accuracy
    highestAccuracy = {"ratio": -1}
    for songResult in accuracyList:
      if songResult["ratio"] > highestAccuracy["ratio"]:
        highestAccuracy = songResult
    
    songData["ratio"] = highestAccuracy["ratio"]
    songData["id"] = highestAccuracy["id"]
    songData["uploader"] = highestAccuracy["uploader"]
    songData["url"] = "https://www.youtube.com/watch?v=" + highestAccuracy["id"]

    return songData