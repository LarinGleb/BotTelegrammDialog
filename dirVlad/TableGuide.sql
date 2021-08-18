USE `rpnac5`;

drop table DirVlad;
drop table DirVladDescription;

CREATE TABLE `DirVlad` (
    id MEDIUMINT NOT NULL AUTO_INCREMENT,
    issue CHAR(8),
    Town CHAR(255) NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE `DirVladDescription` (
    id MEDIUMINT NOT NULL AUTO_INCREMENT,
    issue CHAR(8),
    issueID CHAR(8),
    Town CHAR(255) NOT NULL,
    Descriptions CHAR(255) NOT NULL,
    PRIMARY KEY (id)
);

INSERT INTO DirVlad (Town)
VALUES
("Москва");

INSERT INTO DirVladDescription (Town, Descriptions)
VALUES
("Москва", "Собор василия офаоиыловариловфра");
