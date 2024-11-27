-- Keep a log of any SQL queries you execute as you solve the mystery.

-- CHECK REPORTS GIVEN THE DATE AND LOCATION OF THEFT
SELECT * FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
-- 295 | 2020 | 7 | 28 | Chamberlin Street |
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time —
-- each of their interview transcripts mentions the courthouse.

-- CHECK INTERVIEWS
SELECT * FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;
--158 | Jose | 2020 | 7 | 28 | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
--159 | Eugene | 2020 | 7 | 28 | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
--160 | Barbara | 2020 | 7 | 28 | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
--161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- CHECK COURTHOUSE LOGS
SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 5 AND 25;
--260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
--262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
--263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
--264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
--266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
--267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55

-- CHECK ATM
SELECT * FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type LIKE "%with%";
--246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
--264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
--266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
--267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
--269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
--288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
--313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
--336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35

-- CHECK phone calls
SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration BETWEEN 0 AND 59;
--221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
--224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
--233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
--251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
--254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
--255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
--261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
--279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
--281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54

-- CHECK FLIGHT
SELECT * FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville");
-- 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20

-- CHECK PASSENGERS
SELECT * FROM passengers JOIN flights ON passengers.flight_id = flights.id WHERE id = 36;
--36 | 7214083635 | 2A | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
--36 | 1695452385 | 3B | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
--36 | 5773159633 | 4A | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
--36 | 1540955065 | 5C | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
--36 | 8294398571 | 6C | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
--36 | 1988161715 | 6D | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
--36 | 9878712108 | 7A | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
--36 | 8496433585 | 7B | 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20

-- CHECK NAMES THAT MADE CALL, TOOK PLANE AND DROVE AWAY FROM COURTHOUSE
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration BETWEEN 0 AND 59) AND passport_number IN (SELECT passport_number FROM passengers JOIN flights ON passengers.flight_id = flights.id WHERE id = 36) AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 5 AND 25);
--Roger
--Evelyn
--Ernest

-- CHECK NAMES THAT MADE TRANSACTION ON ATM
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type LIKE "%with%"));
--Bobby
--Elizabeth
--Victoria
--Madison
--Roy
--Danielle
--Russell
--Ernest

-- NAME THAT MATCHES ALL GIVEN FACTS IS ERNEST!

-- CHECK DESTINATION OF ERNEST'S FLIGHT
SELECT city FROM airports WHERE id = 4;
-- London

-- CHECK ERNEST'S ACCOMPLICE
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration BETWEEN 0 AND 59 AND caller IN (SELECT phone_number FROM people WHERE name = "Ernest"));
-- Berthold