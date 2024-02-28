-- Keep a log of any SQL queries you execute as you solve the mystery.
--Who the thief is,
--What city the thief escaped to, and
--Who the thief’s accomplice is who helped them escape
--All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street.

--Checking police report for the crime date
SELECT id, street, description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;
-- New Fact: Crime address - Humphrey Street bakery
-- New Fact: Crime time    - 10:15am
-- New Fact: Interviews were conducted today with three witnesses who were present at the time
--           – each of their interview transcripts mentions the bakery.

--Checking witnesses interviews
SELECT name, year, month, day, transcript FROM interviews WHERE transcript LIKE '%bakery%' AND year = 2021 AND month = 7 AND day = 28;
-- Name: Ruth
-- Sometime within ten minutes of the theft,
-- I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot,
-- you might want to look for cars that left the parking lot in that time frame.

-- TODO: Check parking records

-- Name: Eugene
-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- TODO Check ATM on Leggett Street records for this date morning.

-- Name: Raymond
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- TODO Check phone calls, it can help to bound thief to Flight bookings base
-- New Fact: Thief planned earliest Flight on July 8 2021

-- Checking parking records
SELECT hour, minute, activity, license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28;
-- Specify the query
SELECT hour, minute, activity, license_plate FROM bakery_security_logs
                                             WHERE year = 2021 AND month = 7 AND day = 28
                                             AND activity='exit' AND hour=10 AND minute>=15 AND minute <=25;
-- Now we can get the list of persons by license plates
SELECT id, name, phone_number, passport_number FROM people WHERE license_plate IN
        (SELECT license_plate FROM bakery_security_logs
                                             WHERE year = 2021 AND month = 7 AND day = 28
                                             AND activity='exit' AND hour=10 AND minute>=15 AND minute <=25);

-- Suspects list
--+--------+---------+----------------+-----------------+
--|   id   |  name   |  phone_number  | passport_number |
--+--------+---------+----------------+-----------------+
--| 221103 | Vanessa | (725) 555-4692 | 2963008352      |
--| 243696 | Barry   | (301) 555-4174 | 7526138472      |
--| 396669 | Iman    | (829) 555-5269 | 7049073643      |
--| 398010 | Sofia   | (130) 555-0289 | 1695452385      |
--| 467400 | Luca    | (389) 555-5198 | 8496433585      |
--| 514354 | Diana   | (770) 555-1861 | 3592750733      |
--| 560886 | Kelsey  | (499) 555-9472 | 8294398571      |
--| 686048 | Bruce   | (367) 555-5533 | 5773159633      |
--+--------+---------+----------------+-----------------+

-- Check ATM transactions (filter data with suspicious car plates owners)
SELECT * FROM atm_transactions JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type='withdraw' AND atm_location='Leggett Street'
AND bank_accounts.person_id IN
(SELECT id FROM people WHERE license_plate IN
        (SELECT license_plate FROM bakery_security_logs
                                             WHERE year = 2021 AND month = 7 AND day = 28
                                             AND activity='exit' AND hour=10 AND minute>=15 AND minute <=25));

-- Shorten Suspects list
--+--------+---------+----------------+-----------------+
--|   id   |  name   |  phone_number  | passport_number |
--+--------+---------+----------------+-----------------+
--| 396669 | Iman    | (829) 555-5269 | 7049073643      |
--| 467400 | Luca    | (389) 555-5198 | 8496433585      |
--| 514354 | Diana   | (770) 555-1861 | 3592750733      |
--| 686048 | Bruce   | (367) 555-5533 | 5773159633      |
--+--------+---------+----------------+-----------------+


-- Checking phone calls less than a minute
SELECT * FROM phone_calls JOIN people ON people.phone_number=phone_calls.caller WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
AND people.id IN (396669, 467400, 514354, 686048);

-- Shorten Suspects list
--+--------+---------+----------------+-----------------+
--|   id   |  name   |  phone_number  | passport_number |
--+--------+---------+----------------+-----------------+
--| 514354 | Diana   | (770) 555-1861 | 3592750733      |
--| 686048 | Bruce   | (367) 555-5533 | 5773159633      |
--+--------+---------+----------------+-----------------+

-- Get names of Persons who recieved calls from suspects
SELECT id, name, phone_number, passport_number FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls JOIN people ON people.phone_number=phone_calls.caller WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
AND people.id IN (514354, 686048));

--Potencial thief's accompliances
--+--------+--------+----------------+-----------------+
--|   id   |  name  |  phone_number  | passport_number |
--+--------+--------+----------------+-----------------+
--| 847116 | Philip | (725) 555-3243 | 3391710505      |
--| 864400 | Robin  | (375) 555-8161 | NULL            |
--+--------+--------+----------------+-----------------+


-- Now, let's check earliest flight bookings for the next day

SELECT * FROM flights
    WHERE origin_airport_id = (SELECT id FROM airports WHERE city='Fiftyville')
    AND year = 2021 AND month = 7 AND day = 29
    ORDER BY hour, minute LIMIT 1;

--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
--+----+-------------------+------------------------+------+-------+-----+------+--------+

-- Check for destination
SELECT * FROM airports WHERE id = 4;

--+----+--------------+-------------------+---------------+
--| id | abbreviation |     full_name     |     city      |
--+----+--------------+-------------------+---------------+
--| 4  | LGA          | LaGuardia Airport | New York City |
--+----+--------------+-------------------+---------------+

-- Check suspects-passenges intersection

SELECT * FROM passengers WHERE flight_id = 36 AND passport_number IN (3592750733, 5773159633, 3391710505);

--1 Match!
--+-----------+-----------------+------+
--| flight_id | passport_number | seat |
--+-----------+-----------------+------+
--| 36        | 5773159633      | 4A   |
--+-----------+-----------------+------+

-- So the thief is
-- Bruce
-- and his accomplice is Robin
-- Bruce escaped to New York City
