"""
    Test url

"""

import requests
import time

def time_url_open(url):
    if ("https" or "http") not in url:
        url = "https://" + url
    start_time = time.time()
    requests.get (url)
    end_time = time.time()
    loading_time = end_time - start_time
    return loading_time

url = input("Enter URL to test: ")
print(f"\n{url} loaded in {time_url_open(url):.2} seconds.")
