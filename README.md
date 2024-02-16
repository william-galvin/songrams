# Song-grams

## Installation
1. Clone and `cd` into this repo
2. `make`
3. (for advanced usage) `pip install -r playlist/requirements.txt`

## Usage
```bash
$ ./songrams "<some phrase here>"
```
The output will be lines in pairs where line 2n is the nth song and line 2n+1 is the nth artist. 

For example:

```
$ ./songrams "Hello world and goodbye world"

Hello World
Nik Kershaw
And Goodbye
Flying Saucer Attack and Roy Montgomery
World
Mint Royale
```

## Advanced usage
This program can be used to produce images of playlists (1), or to add songs to a spotify playlist (2).
1. This requires a [lastfm API key](https://www.last.fm/api/authentication), which needs to be added to `playlist/config.yml`.
2. This requires a [spotify API key](https://developer.spotify.com/documentation/web-api), which needs to be added to `playlist/config.yml` alongside other account information (e.g. username) and the name of the playlist to add songs to. If the playlist doesn't exist, it will be created

To use these features, pipe the output from `./songgrams` into `playlist/main.py` with the `--format` argument. For example:

```bash
./songrams "hello images and pictures" | playlist/main.py --format image -o foo.png
```
or 
```bash
./songrams "howdy internet" | playlist/main.py --format spotify
```

There is a known issue in which a song in `data/titles.txt` is not on spotify. TODO: remove them.



