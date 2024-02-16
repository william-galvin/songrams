import spotipy
import yaml
 

def get_playlist_id(sp, playlist_name, config):
    # Gets the playlist id from the playlist name
    playlists = sp.user_playlists(config["USERNAME"])
    for playlist in playlists["items"]:
        if playlist["name"] == playlist_name:
            return playlist["id"]
    return None


def add_song(sp, song_name, artist_name, config):
    if get_playlist_id(sp, config["PLAYLIST"], config) is None:
        sp.user_playlist_create(config["USERNAME"], config["PLAYLIST"])

    song_id = get_song_id(sp, song_name, artist_name)
    if song_id == None:
        print_with_red_text(f"Song not found: {song_name}")
    else:
        sp.user_playlist_add_tracks(config["USERNAME"], get_playlist_id(sp, config["PLAYLIST"], config), [song_id])
        print_with_green_text(f"Song added: {song_name}")
    print()


def get_song_id(sp, song_name, artist_name):
    # Gets the song id from the song name and artist name
    results = sp.search(q='artist:' + artist_name + ' track:' + song_name, type='track')
    try:
        return (results["tracks"]["items"][0]["id"])
    except:
        return None
    

def print_with_green_text(text):
    print("\033[1;32m" + text + "\033[0m", end = "")

def print_with_red_text(text):
    print("\033[1;31m" + text + "\033[0m", end = "")

def print_with_blue_text(text):
    print("\033[1;34m" + text + "\033[0m", end = "")

def print_with_yellow_text(text):
    print("\033[1;33m" + text + "\033[0m", end = "")

def print_with_bold_text(text):
    print("\033[1m" + text + "\033[0m", end = "")



def get_spotify(config):
    return spotipy.Spotify(
        auth_manager=spotipy.SpotifyOAuth(
        client_id=config["CLIENT_ID"],
        client_secret=config["CLIENT_SECRET"],
        redirect_uri=config["REDIRECT_URI"],
        scope=config["SCOPE"])
    )


