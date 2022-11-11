CREATE TABLE repository_eduard240300 (
  id INT(11) PRIMARY KEY,
  type VARCHAR(200) NOT NULL,
  name VARCHAR(200) NOT NULL,
  page_or_time VARCHAR(200) NOT NULL
);

CREATE TABLE user_details (
  user_id INT(11) PRIMARY KEY,
  user_username VARCHAR(200) NOT NULL,
  user_password VARCHAR(200) NOT NULL,
  user_name VARCHAR(200) NOT NULL,
  user_security_hint VARCHAR(200) NOT NULL,
  user_security_phrase VARCHAR(200) NOT NULL
);
