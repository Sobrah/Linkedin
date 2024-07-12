CREATE TABLE IF NOT EXISTS accounts (
	accountID SERIAL PRIMARY KEY,
	username TEXT NOT NULL UNIQUE,
	password TEXT NOT NULL,
	email TEXT NOT NULL UNIQUE,
	phoneNumber TEXT NOT NULL,
	skill TEXT NOT NULL,
	firstName TEXT NOT NULL,
	lastName TEXT,
	isCompany BOOLEAN NOT NULL,
	biography TEXT
);

CREATE TABLE IF NOT EXISTS contents (
	contentID SERIAL PRIMARY KEY,
	senderID INTEGER,
	timeSent TEXT NOT NULL,
	contentText TEXT,

	FOREIGN KEY (senderID) REFERENCES accounts (accountID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS posts (
	postID SERIAL PRIMARY KEY,
	contentID INTEGER,
	repostCounter INTEGER NOT NULL DEFAULT 0,
	isReposted BOOLEAN NOT NULL,

	FOREIGN KEY (contentID) REFERENCES contents (contentID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS jobs (
	jobID SERIAL PRIMARY KEY,
	companyID INTEGER,
	title TEXT NOT NULL,
	skill TEXT NOT NULL,
	workplaceType TEXT NOT NULL,
	location TEXT NOT NULL,
	type TEXT NOT NULL,

	FOREIGN KEY (companyID) REFERENCES accounts (accountID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS jobsRequests (
	jobRequestID SERIAL PRIMARY KEY,
	accountID INTEGER,
	jobID INTEGER,
	isAccepted BOOLEAN DEFAULT FALSE,

	FOREIGN KEY (accountID) REFERENCES accounts (accountID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE,
	
	FOREIGN KEY (jobID) REFERENCES jobs (jobID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS connections (
	connectionID SERIAL PRIMARY KEY,
	followerID INTEGER,
	followingID INTEGER,

	FOREIGN KEY (followerID) REFERENCES accounts (accountID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE,

	FOREIGN KEY (followingID) REFERENCES accounts (accountID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS likes (
	likeID SERIAL PRIMARY KEY,
	whoLikedID INTEGER,
	postID INTEGER,

	FOREIGN KEY (whoLikedID) REFERENCES accounts (accountID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE,

	FOREIGN KEY (postID) REFERENCES posts (postID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS connectionRequests (
	connectionRequestID SERIAL PRIMARY KEY,
	followerID INTEGER,
	followingID INTEGER,

	FOREIGN KEY (followerID) REFERENCES accounts (accountID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE,

	FOREIGN KEY (followingID) REFERENCES accounts (accountID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS comments (
	commentID SERIAL PRIMARY KEY,
	contentID INTEGER,
	postID INTEGER,

	FOREIGN KEY (contentID) REFERENCES contents (contentID)
		ON UPDATE NO ACTION
		ON DELETE CASCADE,

	FOREIGN KEY (postID) REFERENCES posts (postID)
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