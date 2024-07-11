PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS 'accounts' (
	'accountID' INTEGER PRIMARY KEY,
	'username' TEXT NOT NULL UNIQUE,
	'password' TEXT NOT NULL,
	'email' TEXT NOT NULL UNIQUE,
	'phoneNumber' TEXT NOT NULL,
	'skill' TEXT NOT NULL,
	'firstName' TEXT NOT NULL,
	'lastName' TEXT,
	'isCompany' INTEGER NOT NULL,
	'bio' TEXT
);

CREATE TABLE IF NOT EXISTS 'contents' (
	'contentID' INTEGER PRIMARY KEY,
	'senderID' INTEGER,
	'timeSent' TEXT NOT NULL,
	'contentText' TEXT,

	FOREIGN KEY ('senderID') REFERENCES 'accounts' ('accountID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS 'posts' (
	'postID' INTEGER PRIMARY KEY,
	'contentID' INTEGER,
	'repostCounter' INTEGER NOT NULL DEFAULT 0,
	'isReposted' INTEGER NOT NULL,

	FOREIGN KEY ('contentID') REFERENCES 'contents' ('contentID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS 'jobs' (
	'jobID' INTEGER PRIMARY KEY,
	'companyID' INTEGER,
	'title' TEXT NOT NULL,
	'skill' TEXT NOT NULL,
	'workplaceType' TEXT NOT NULL,
	'location' TEXT NOT NULL,
	'type' TEXT NOT NULL,

	FOREIGN KEY ('companyID') REFERENCES 'accounts' ('accountID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS 'jobsRequests' (
	'jobRequestID' INTEGER PRIMARY KEY,
	'accountID' INTEGER,
	'jobID' INTEGER,
	'isAccepted' INTEGER DEFAULT 0,

	FOREIGN KEY ('accountID') REFERENCES 'accounts' ('accountID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
	
	FOREIGN KEY ('jobID') REFERENCES 'jobs' ('jobID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS 'connections' (
	'connectionID' INTEGER PRIMARY KEY,
	'followerID' INTEGER,
	'followingID' INTEGER,

	FOREIGN KEY ('followerID') REFERENCES 'accounts' ('accountID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE

	FOREIGN KEY ('followingID') REFERENCES 'accounts' ('accountID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS 'likes' (
	'likeID' INTEGER PRIMARY KEY,
	'whoLikedID' INTEGER,
	'postID' INTEGER,

	FOREIGN KEY ('whoLikedID') REFERENCES 'accounts' ('accountID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE

	FOREIGN KEY ('postID') REFERENCES 'posts' ('postID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS 'connectionRequests' (
	'connectionRequestID' INTEGER PRIMARY KEY,
	'followerID' INTEGER,
	'followingID' INTEGER,

	FOREIGN KEY ('followerID') REFERENCES 'accounts' ('accountID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE

	FOREIGN KEY ('followingID') REFERENCES 'accounts' ('accountID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS 'comments' (
	'commentID' INTEGER PRIMARY KEY,
	'contentID' INTEGER,
	'postID' INTEGER,

	FOREIGN KEY ('contentID') REFERENCES 'contents' ('contentID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE

	FOREIGN KEY ('postID') REFERENCES 'posts' ('postID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS 'directMessages' (
	'directMessageID' INTEGER PRIMARY KEY,
	'contentID' INTEGER,
	'senderID' INTEGER,
	'receiverID' INTEGER,

	FOREIGN KEY ('contentID') REFERENCES 'contents' ('contentID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE

	FOREIGN KEY ('senderID') REFERENCES 'accounts' ('accountID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE

	FOREIGN KEY ('receiverID') REFERENCES 'accounts' ('accountID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);