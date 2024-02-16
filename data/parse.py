from sys import stdin

delim_in, delim_out = "<SEP>", "|"
songs = []

for line in stdin:
    _, _, artist, title = line.split(delim_in)
    songs.append((title, artist))

songs.sort(key=lambda x: len(x[0]), reverse=True)

for (title, artist) in songs:
    print(f"{title.strip()}{delim_out}{artist}")

exit(0)

