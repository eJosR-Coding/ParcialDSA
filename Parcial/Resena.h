#pragma once

#ifndef REVIEW_H
#define REVIEW_H

#include "Dependencies.h"
#include <vector>

class Resena {
private:
    int id;           
    string author;     
    string text;     
    int rating;             
   vector<Resena*> responses;

public:

    Resena(int id, const string& author, const string& text, int rating)
        : id(id), author(author), text(text), rating(rating) {}


    void addResponse(Resena* response) {
        responses.push_back(response);
    }


    void show() const {
        cout << "ID: " << id << std::endl;
        cout << "Author: " << author << std::endl;
        cout << "Rating: " << rating << std::endl;
        cout << "Text: " << text << std::endl;

        if (!responses.empty()) {
            std::cout << "Responses:" << std::endl;
            for (const Resena* response : responses) {
                response->show();
            }
        }
    }

   
};

#endif
