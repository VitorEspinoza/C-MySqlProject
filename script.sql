CREATE DATABASE BANK;
USE BANK;
CREATE TABLE client
(
    id INT
    AUTO_INCREMENT PRIMARY KEY,
    CPF varchar
    (11),
    RG VARCHAR
    (30),
    Name varchar
    (40),
    Address varchar
    (40),
	Phone VARCHAR
    (11),
    MaritalStatus ENUM
    ('SINGLE', 'MARRIED'),
    active TINYINT
    (1) DEFAULT 1 
);

    CREATE TABLE Agency
    (
        Name varchar(40),
        Address varchar(40),
        AgencyCode varchar(255) PRIMARY KEY
    );

    CREATE TABLE Account (
    AccountNumber varchar(255) PRIMARY KEY,
    Balance double,
    AgencyCode varchar
    (255),
    fk_Client_ID INT,
	password varchar
    (255),
	active TINYINT
    (1) DEFAULT 1,    
    FOREIGN KEY
    (AgencyCode) REFERENCES Agency
    (AgencyCode),
    FOREIGN KEY
    (fk_Client_ID) REFERENCES client
    (id)
);

    CREATE TABLE Transaction (
    fk_Account_AccountNumber varchar(255),
    target_account varchar(255),
    PaymentType ENUM('CREDIT', 'DEBIT'),
    Amount double,
    Date DATE,
    Hour TIME,
    FOREIGN KEY
    (fk_Account_AccountNumber) REFERENCES Account
    (AccountNumber)
);

    INSERT INTO agency
        (name, address, agencyCode)
    VALUES
        ('cbank', 'cbank.com', 777);