#!/usr/bin/env python

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

import argparse
import sys
import yaml
import requests

from spotify import get_spotify, add_song

config = yaml.safe_load(open("playlist/config.yaml"))
LASTFM_API_KEY =config["LASTFM_API_KEY"]
LASTFM_BASE_URL = "http://ws.audioscrobbler.com/2.0/"


def get_album_cover(title: str, artist: str, n_retries: int = 10) -> Image:
    print(title, artist)
    params = {
        "method": "track.getinfo",
        "track": title,
        "artist": artist,
        "format": "json",
        "limit": 1,
        "api_key": LASTFM_API_KEY,
    }

    for _ in range(n_retries):
        try:
            response = requests.get(LASTFM_BASE_URL, params=params, timeout=1).json()
            img_url = response["track"]["album"]["image"][-1]["#text"]
            return Image.open(requests.get(img_url, stream=True, timeout=1).raw)
        except:
            pass

    return Image.open(config["default_album"])


def get_font(text: str, font_path: str, max_width: int, size: int) -> ImageFont.FreeTypeFont:
    font = ImageFont.FreeTypeFont(font_path, size)
    while font.getlength(text) > max_width:
        font = ImageFont.FreeTypeFont(font_path, font.size - 1)
    return font


def get_titles_artists():
    lines = [line.strip() for line in sys.stdin.readlines()]
    n_songs = len(lines) // 2

    result = []

    for i in range(n_songs):
        title, artist = lines[2 * i], lines[2 * i + 1]
        result.append((title, artist))

    return result


def make_img(output_file):

    titles_and_artists = get_titles_artists()
    n_songs = len(titles_and_artists)
    

    base = Image.new(
        mode="RGB", 
        size=(config["width"], config["v_pad"] + config["px_per_song"] * n_songs),
        color=(config["bg_color"]),
    )
    img = ImageDraw.Draw(base)

    album_size = int(config["px_per_song"] * 0.8)
    x = config["h_pad"] * 2 + album_size



    for i, (title, artist) in enumerate(titles_and_artists):
        y = config["v_pad"] + config["px_per_song"] * i
        max_width = config["width"] - (config["h_pad"] * 3 + album_size)
        
        img.text(
            xy=(x, y), 
            text=title,
            fill=config["main_text_color"],
            font=get_font(
                text=title,
                font_path=config["main_font"],
                max_width=max_width,
                size=config["main_font_size"],
            )
        )
        img.text(
            xy=(x, y + config["main_font_size"] + config["v_pad"] / 2), 
            text=artist,
            fill=config["sub_text_color"],
            font=get_font(
                text=artist,
                font_path=config["sub_font"],
                max_width=max_width,
                size=config["sub_font_size"],
            )
        )

        album = (get_album_cover(title, artist))
        base.paste(
            im=album.resize((album_size, album_size), 3), 
            box=(config["h_pad"], y)
        )

    if output_file is not None:
        base.save(output_file)
    else:
        base.show()


def add_to_spotify():
    sp = get_spotify(config)
    for title, artist in get_titles_artists():
        add_song(sp, title, artist, config)
    

def main():
    parser = argparse.ArgumentParser(formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument(
        "--format",
        "-f",
        default="image",
        choices=["image", "spotify"],
        help=("Choice for output; image will create an image."
              "spotify will add to a spotify playlist"),
    )
    parser.add_argument(
        "-o", 
        "--out", 
        help=("Path to save image output file," 
              "if --format is set to 'image'. If unset, image will show in window")
    )

    args = parser.parse_args()

    if args.format == "image":
        make_img(args.out)
    else:
        add_to_spotify()


if __name__ == "__main__":
    main()