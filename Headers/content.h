#ifndef CONTENT_H
#define CONTENT_H

#include <QVector>
#include <iostream>

using namespace std;

class Time
{
private:
    string day;
    string month;
    string year;
    string hour;
    string minute;
    string second;

public:
    void set_day(string);
    void set_month(string);
    void set_year(string);
    void set_hour(string);
    void set_minute(string);
    void set_second(string);
    string get_day() const;
    string get_month() const;
    string get_year() const;
    string get_hour() const;
    string get_minute() const;
    string get_second() const;
};

class content
{
private:
    string sender_id;
    Time Time_sent;
    string Content_text;

public:
    void set_sender_id(string);
    void set_Time_sent(Time);
    void set_Content_text(string);
    string get_sender_id() const;
    Time get_Time_sent() const;
    string get_Content_text() const;
};

class Direct_Message : private content
{
private:
    string Message_ID;
    string To_who;

public:
    void set_Message_ID(string);
    void set_To_who(string);
    string get_Message_ID() const;
    string get_To_who() const;
};

class Comment : private content
{
private:
    string Post_ID;
    string comment_ID;

public:
    void set_Post_ID(string);
    void set_comment_ID(string);
    string get_Post_ID() const;
    string get_comment_ID() const;
};

class Like
{
private:
    string Who_liked_ID;
    string Like_ID;
    Time When_liked;

public:
    void set_Who_liked_ID(string);
    void set_Like_ID(string);
    void set_When_liked(Time);
    string get_Who_liked_ID() const;
    string get_Like_ID() const;
    Time get_When_liked() const;
};

class Post : private content
{
private:
    string Post_ID;
    int Repost_counter;
    QVector<Like> Likes;
    QVector<Comment> Comments;

public:
    void set_Post_ID(string);
    void set_Repost_counter(int);
    string get_Post_ID() const;
    int get_Repost_counter() const;
    QVector<Like> get_Likes() const;
    QVector<Comment> get_Comments() const;
    void add_Repost_counter();
};

#endif // CONTENT_H
