PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS 'accounts' (
	'accountID' INTEGER PRIMARY KEY,
	'username' TEXT NOT NULL UNIQUE,
	'password' TEXT NOT NULL,
	'email' TEXT NOT NULL UNIQUE,
	'phoneNumber' TEXT,
	'skill' TEXT,
	'firstName' TEXT,
	'lastName' TEXT,
	'isCompany' INTEGER,
	'companyName' TEXT
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

	FOREIGN KEY ('contentID') REFERENCES 'contents' ('contentID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS 'jobs' (
	'jobID' INTEGER PRIMARY KEY,
	'companyID' INTEGER,
	'title' TEXT NOT NULL,
	'workplaceType' TEXT NOT NULL,
	'location' TEXT NOT NULL,
	'type' TEXT NOT NULL,

	FOREIGN KEY ('companyID') REFERENCES 'accounts' ('accountID')
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);