#include "Headers/content.h"

void Time::set_day(string day)
{
    this->day = day;
}

void Time::set_month(string month)
{
    this->month = month;
}

void Time::set_year(string year)
{
    this->year = year;
}

void Time::set_hour(string hour)
{
    this->hour = hour;
}

void Time::set_minute(string minute)
{
    this->minute = minute;
}

void Time::set_second(string second)
{
    this->second = second;
}

string Time::get_day() const
{
    return day;
}

string Time::get_month() const
{
    return month;
}

string Time::get_year() const
{
    return year;
}

string Time::get_hour() const
{
    return hour;
}

string Time::get_minute() const
{
    return minute;
}

string Time::get_second() const
{
    return second;
}

void content::set_sender_id(string sender_id)
{
    this->sender_id = sender_id;
}

void content::set_Time_sent(Time Time_sent)
{
    this->Time_sent = Time_sent;
}

void content::set_Content_text(string Content_text)
{
    this->Content_text = Content_text;
}

string content::get_sender_id() const
{
    return sender_id;
}

Time content::get_Time_sent() const
{
    return Time_sent;
}

void Direct_Message::set_Message_ID(string Message_ID)
{
    this->Message_ID = Message_ID;
}

void Direct_Message::set_To_who(string To_who)
{
    this->To_who = To_who;
}

string Direct_Message::get_Message_ID() const
{
    return Message_ID;
}

string Direct_Message::get_To_who() const
{
    return To_who;
}

void Comment::set_Post_ID(string Post_ID)
{
    this->Post_ID = Post_ID;
}

void Comment::set_comment_ID(string comment_ID)
{
    this->comment_ID = comment_ID;
}

string Comment::get_Post_ID() const
{
    return Post_ID;
}

string Comment::get_comment_ID() const
{
    return comment_ID;
}

void Like::set_Who_liked_ID(string Who_liked_ID)
{
    this->Who_liked_ID = Who_liked_ID;
}

void Like::set_Like_ID(string Like_ID)
{
    this->Like_ID = Like_ID;
}

void Like::set_When_liked(Time When_liked)
{
    this->When_liked = When_liked;
}

string Like::get_Who_liked_ID() const
{
    return Who_liked_ID;
}

string Like::get_Like_ID() const
{
    return Like_ID;
}

Time Like::get_When_liked() const
{
    return When_liked;
}

void Post::set_Post_ID(string Post_ID)
{
    this->Post_ID = Post_ID;
}

void Post::set_Repost_counter(int Repost_counter)
{
    this->Repost_counter = Repost_counter;
}

string Post::get_Post_ID() const
{
    return Post_ID;
}

int Post::get_Repost_counter() const
{
    return Repost_counter;
}

QVector<Like> Post::get_Likes() const
{
    return Likes;
}

QVector<Comment> Post::get_Comments() const
{
    return Comments;
}

void Post::add_Repost_counter()
{
    Repost_counter++;
}
