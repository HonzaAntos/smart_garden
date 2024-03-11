
/*creating a table in the database*/
CREATE TABLE sensordata (
  id int(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  value1 varchar(10),
  value2 varchar(10),
  value3 varchar(10),
  value4 varchar(10),
  reading_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

