#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <curl/curl.h>
#include "../libraries/json.hpp"
#include "./record_list.h"

using namespace std;
using json = nlohmann::json;

class Search {
  public:
  RecordList record_list;

  string fetch_url(string url) {
    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
      if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
      }

    return readBuffer;
  }

  json fetch_json(string url) {
    string res = fetch_url(url);
    return json::parse(res);
  }

  json search_results_json(string song_name) {
    string url = "https://saavn.me/search/songs?query=" + song_name;
    return fetch_json(url);
  }

  void generate_records(json search_results_json) {
    json songs = search_results_json["data"]["results"];

    json song;
    for (int i = 0; i < songs.size(); i++) {
      song = songs.at(i);
      record_list.records.push_back(
        Record(song["name"], song["primaryArtists"], 0)
      );
    }
  }

  void search(string query) {
    json song_json = search_results_json("Strawberry");

    generate_records(song_json);
    record_list.display();
  }

  private:
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
  }
};

#endif
