#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <algorithm>
#include <curl/curl.h>
#include "../libraries/json.hpp"
#include "./record_list.h"

using namespace std;
using json = nlohmann::json;

class Search : public RecordList {
  public:
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
    string url = "https://saavn.me/search/songs?query=" + space2plus(song_name);
    return fetch_json(url);
  }

  void generate_records(json search_results_json) {
    json songs = search_results_json["data"]["results"];

    json song;
    for (int i = 0; i < songs.size(); i++) {
      song = songs.at(i);
      records.push_back(
        Record(song["name"], song["primaryArtists"], 0)
      );
    }
  }

  void search(string query) {
    json song_json = search_results_json(query);

    generate_records(song_json);
  }

  protected:
  // All of these are overrides for the RecordList class
  // to remove the count column since that's not need for search results
  int full_row_width() {
    return COLUMN_WIDTH * 2 + 1;
  }

  string column_titles() {
    stringstream titles;
    titles << "#" << setw(COLUMN_WIDTH) << "Title" << setw(COLUMN_WIDTH) << "Artist" << setw(COLUMN_WIDTH) << endl;
    return titles.str();
  }

  string record_row_format(Record rec) {
    stringstream output;
    output << rec.name << setw(COLUMN_WIDTH) << rec.artist;
    return output.str();
  }

  string space2plus(std::string text) {
    std::replace(text.begin(), text.end(), ' ', '+');
    return text;
  }

  private:
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
  }
};

#endif
