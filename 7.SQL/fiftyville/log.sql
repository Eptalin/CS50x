-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Search crime scene reports for the incident:
    -- Theft of the CS50 Duck
    -- 28/07/2023 Humphrey St
    SELECT * FROM crime_scene_reports
    WHERE year = 2023
    AND month = 7
    AND day = 28;


    -- id = 125
    -- Time of incident: 10:15am
    -- Location: Bakery
    -- 3 witnesses were interviewed. All mentioned "bakery".
    -- Another theft occured at 3:01am on Boyce avenue. 2 witnesses. Possible connection? (id = 294)


    -- Search for interviews which mention "bakery"
    SELECT * FROM interviews
    WHERE transcript LIKE '%bakery%';
    -- Obtained 3 leads from the witnesses, Ruth, Eugene, Raymond. Follow up each individually.


-- Lead 1 - Ruth: Within 10min of theft (10:25), thief exited bakery parking lot in a car. Likely on security footage.
    -- Search security footage for cars present during the crime and leaving within that window.
    SELECT * FROM bakery_security_logs
    WHERE year = 2023 AND month = 7 AND day = 28
    AND hour = 10
    AND minute <= 30
    -- 8 card left within that window
    -- 5P2BI95, 94KL13, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7J, 0NTHK55


    -- Search people to find who owns these cars:         TODO!!!!!!!!!!!!!! Re-seach plates!!!!
    SELECT * FROM people
    WHERE license_plate IN (
        '5P2BI95', '94KL13X', '6P58WS2', '4328GD8',
        'G412CB7', 'L93JTIZ', '322W7JE', '0NTHK55'
    );


-- SUSPECT LIST:
    --   Name  |   Phone No.    |   Passport No.  |   License Plate |   Acc. No.
    -- Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95         |
    -- Barry   | (301) 555-4174 | 7526138472      | 6P58WS2         |
    -- Iman    | (829) 555-5269 | 7049073643      | L93JTIZ         |
    -- Sofia   | (130) 555-0289 | 1695452385      | G412CB7         |
    -- Luca    | (389) 555-5198 | 8496433585      | 4328GD8         |
    -- Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55         |
    -- Diana   | (770) 555-1861 | 3592750733      | 322W7JE         |
    -- Bruce   | (367) 555-5533 | 5773159633      | 94KL13X         |


-- Lead 2 - Eugene: Some time before the theft (maybe morning), the thief used the ATM on Leggett Street to withdraw.
    -- Obtain bank account numbers for the suspects, then search the ATM records
    SELECT people.name, bank_accounts.account_number FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE name IN ('Vanessa', 'Barry', 'Iman', 'Sofia', 'Luca', 'Kelsey');
    -- No hits for Vanessa, Sofia, Kelsey


    -- SUSPECT LIST Version 2:
    --   Name  |   Phone No.    |   Passport No.  |   License Plate |   Acc. No.
    -- Barry   | (301) 555-4174 | 7526138472      | 6P58WS2         | 56171033
    -- Iman    | (829) 555-5269 | 7049073643      | L93JTIZ         | 25506511
    -- Luca    | (389) 555-5198 | 8496433585      | 4328GD8         | 28500762
    -- Diana   | (770) 555-1861 | 3592750733      | 322W7JE         | 26013199
    -- Bruce   | (367) 555-5533 | 5773159633      | 94KL13X         | 49610011


    -- Check these account numbers against the ATM data for the morning of the 28th.
    SELECT * FROM atm_transactions
    WHERE year = 2023 AND month = 7 AND day = 28
    AND account_number IN (56171033, 25506511, 28500762);
    -- Luca withdrew $48 on Leggett Street
    -- Iman withdrew $48 on Leggett Street
    -- Diana withdrew $35 on Leggett Street
    -- Bruce withdrew $50 on Legget Street

    -- SUSPECT LIST Version 3:
    --   Name  |   Phone No.    |   Passport No.  |   License Plate |   Acc. No.
    -- Iman    | (829) 555-5269 | 7049073643      | L93JTIZ         | 25506511
    -- Luca    | (389) 555-5198 | 8496433585      | 4328GD8         | 28500762
    -- Diana   | (770) 555-1861 | 3592750733      | 322W7JE         | 26013199
    -- Bruce   | (367) 555-5533 | 5773159633      | 94KL13X         | 49610011


-- Lead 3 - Raymond: Thief called someone for <1min while leaving the bakery. Wanted the earliest flight out of town the next day. Asked them to buy it for them.
    -- Check the phone records of the current suspects
    SELECT * FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 90
    AND (caller IN ('(829) 555-5269', '(389) 555-5198', '(770) 555-1861', '(367) 555-5533')
    OR receiver IN ('(829) 555-5269', '(389) 555-5198', '(770) 555-1861', '(367) 555-5533'));
    -- Bruce made 1 call:
        -- (375) 555-8161 for 45 seconds. (Appropriate length)
    -- Diana made 1 call:
        -- (725) 555-3243 for 49 seconds. (Appropriate length)
    -- Luca received 1 call:
        -- (609) 555-5876 for 60 seconds. (Appropriate length)

    -- Find out who the suspects were in contact with
    SELECT * FROM people
    WHERE phone_number IN (
        '(375) 555-8161', '(725) 555-3243', '(609) 555-5876'
    );

-- ACCOMPLICE SUSPECTS
        --  Name   |  Phone No.     |  Passport No.   |  License Plate  |
    -- FOR Bruce - + - - - - - - - -+- - - - - - - - -+- - - - - - - - -+
        -- Robin   | (375) 555-8161 | NULL            | 4V16VO0         |
    -- FOR Diana - + - - - - - - - -+- - - - - - - - -+- - - - - - - - -+
        -- Philip  | (725) 555-3243 | 3391710505      | GW362R6         |
    -- FOR Luca  - + - - - - - - - -+- - - - - - - - -+- - - - - - - - -+
        -- Kathryn | (609) 555-5876 | 6121106406      | 4ZY7I8T         |

    -- Find out the first flight out of Fiftyville on the 29th
    SELECT * FROM flights
    JOIN airports AS origin_airports ON flights.origin_airport_id = origin_airports.id
    JOIN airports AS destination_airports ON flights.destination_airport_id = destination_airports.id
    WHERE year = 2023 AND month = 7 AND day = 29
    AND flights.origin_airport_id = (
        SELECT id FROM airports
        WHERE city = 'Fiftyville')
    ORDER BY hour, minute;
    -- 8:20 Fiftyville (CSF) to LaGuardia, New York (LGA)
    -- 9:30 Fiftyville (CSF) to O'Hare, Chicago (ORD)

    -- Search for passenger list of the flight to NY
    SELECT passengers.seat, people.name FROM passengers
    JOIN people ON people.passport_number = passengers.passport_number
    WHERE flight_id = (
        SELECT id FROM flights
        WHERE year = 2023 AND month = 7 AND day = 29
        AND hour = 8 AND minute = 20
    );
    -- Bruce and Luca were both on the flight to NY

-- Conclusion: Bruce is the thief, and Robin is the accomplice.
    -- Bruce is a better match than Luca as he better fits the witness testimony.
    -- Witness 3 saw him make a call, not receive one.
    -- Bruce's outbound call to Robin best matches the witness testinomy.
