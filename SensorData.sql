/* This script will create the required table on your SQL database. You need to actually CREATE the database first */

CREATE TABLE SensorData (
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    sensor VARCHAR(30) NOT NULL,
    location VARCHAR(30) NOT NULL,
    temperature VARCHAR(10),
    humidity VARCHAR(10),
    pressure VARCHAR(10),
    reading_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
)