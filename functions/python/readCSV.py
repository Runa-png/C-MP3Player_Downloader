import csv

def readCSV(location):
  with open(location, "r") as file:
    csvFile = list(csv.reader(file))

    indexes = csvFile[0]
    csvFile.pop(0)

    compoundedSongData = []

    for row in csvFile:
      songData = {}
      for index in range(0 , len(row)):
        songData[indexes[index]] = row[index]
      compoundedSongData.append(songData)
    
    return compoundedSongData
