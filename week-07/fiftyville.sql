-- ANSWERS.TXT

/*

The THIEF is: Bruce
The city the thief ESCAPED TO: New York
The ACCOMPLICE is: Robin


*/


-- LOG.SQL

-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street";
-- Theft at 10:15 at bakery
-- Three witnesses, transcripts in the bakery. Check transcripts for names and clues
SELECT name, day, month, year, transcript FROM interviews WHERE day = 28 AND month = 7 AND transcript LIKE "%bakery%";

-- Ruth - 10 minutes after theft activity on the parking lot - check cctv for exits
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10;
-- There is licence plate in people so I'll get names here also
SELECT bakery_security_logs.minute, bakery_security_logs.activity, bakery_security_logs.license_plate, people.name FROM bakery_security_logs
    JOIN people ON people.license_plate = bakery_security_logs.license_plate
    WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND bakery_security_logs.activity = "exit";
    -- 7 cases fits here

-- Eugene - Thief was taking money on ATM earlier that morning - check Leggett Street ATM
SELECT * FROM atm_transactions
    WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
    -- Eight results that day, I need names here. Bank accounts table has accounts number and person id, so can be joined to people

-- Get names with transactions
SELECT people.name FROM people
    JOIN bank_accounts ON bank_accounts.person_id = people.id
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw";

    -- Bruce, Diana, Iman, Luca match with Ruth's testemony with parking lot exits

-- Raymond - short call less than a min about booking flight ticket, check phone calls -> then airports
-- Duration is in seconds
SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60;
    -- Nine calls fit here. Need caller names, can be joined with people on the basis of number
-- Get caller names
SELECT people.name FROM people
    JOIN phone_calls ON phone_calls.caller = people.phone_number
    WHERE month = 7 AND day = 28 AND duration < 60;
    -- Bruce, Diana correspond to Ruth and Eugene list - current suspects

-- Get callee names for the accomplice
SELECT people.name FROM people
    JOIN phone_calls ON phone_calls.receiver = people.phone_number
    WHERE month = 7 AND day = 28 AND duration < 60;

-- Check airports in the city
SELECT * FROM airports WHERE city = "Fiftyville"; -- CSF. regional airport
-- Check flights, earliest next day
SELECT * FROM flights -- they work with ids, join them with airports, get names of airports on earliest flighg
SELECT flights.id, flights.origin_airport_id, flights.destination_airport_id, airports.full_name FROM flights
    JOIN airports ON airports.id = flights.origin_airport_id
    WHERE month = 7 AND day = 29 ORDER BY flights.hour ASC LIMIT 1;
    -- earliest flight ID is 36 which left CSF

SELECT flights.id, airports.full_name, airports.city FROM flights
    JOIN airports ON airports.id = flights.destination_airport_id
    WHERE month = 7 AND day = 29 ORDER BY flights.hour ASC LIMIT 1;
    -- Destination is LaGuardia Airport in New York City

-- Check passengers, see who went to New York.
-- So passengers will have flight id (match with flights), fligths will have airports id (match with airports)
-- passengers will also have passport_number, same as people

-- Get names which went to New York
SELECT people.name FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
    JOIN flights ON flights.id = passengers.flight_id
    JOIN airports ON airports.id = flights.destination_airport_id
    WHERE flights.id = 36;
    -- Bruce is the filth - correspond to Ruth, Eugene and Raymond list

-- Need a query to get a name from all four sources
SELECT name from people
    JOIN passengers ON passengers.passport_number = people.passport_number
    JOIN flights ON flights.id = passengers.flight_id
    JOIN airports ON airports.id = flights.destination_airport_id
    WHERE flights.id = 36 AND name IN (
        SELECT people.name FROM people
            JOIN phone_calls ON phone_calls.caller = people.phone_number
            WHERE month = 7 AND day = 28 AND duration < 60
            AND name IN (
                SELECT people.name FROM people
                    JOIN bank_accounts ON bank_accounts.person_id = people.id
                    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
                    WHERE atm_transactions.month = 7 AND atm_transactions.day = 28
                    AND atm_transactions.atm_location = "Leggett Street"
                    AND atm_transactions.transaction_type = "withdraw"
                    AND people.name IN (
                        SELECT people.name FROM bakery_security_logs
                            JOIN people ON people.license_plate = bakery_security_logs.license_plate
                            WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND bakery_security_logs.activity = "exit"
                    )
            )
    ); -- Bruce is the filth

-- Accomplice I can check in the call logs
SELECT name FROM people
    JOIN phone_calls ON phone_calls.receiver = people.phone_number
    WHERE  month = 7 AND day = 28 AND duration < 60 AND caller = (
    SELECT phone_number FROM people WHERE name = 'Bruce'
); -- Robin

