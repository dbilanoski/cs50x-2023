# SQL

Structure Query Language - language for crud actions on a databases

## Databases
# Flat-file databases

Csv file holding some data.

Example: handlin csv with python

```python
import csv

with open("filename.csv", "r") as file:

# Reads rows as lists
reader = csv.reader(file)
# For each csv line do something
for row in reader:
print(row[1])

# Better way - read rows as dictionaires
reader = csv.DictReader(file)
# For each csv line do something
for row in reader:
print(row["col_name"])

```

## Relational databases

Stores data in tables (rows and cols), managed by SQL language.

## SQL

CRUD in SQL
```sql
CREATE, INSERT
SELECT
UPDATE
DELETE
```


Basics

```sql
-- Writing queries

-- Select everything from table favorites
SELECT * FROM favorites;

-- Select some columns from table favourites
SELECT col1name, col2name FROM favourites;

-- Counting
SELECT COUNT(*) FROM favourites; -- returns number of items

-- Counting unique items
SELECT COUNT(DISTINCT(*)) FROM favourites; -- returns number of unique items;

-- Aliasing so column names are shorter in the query result
SELECT COUNT(DISTINCT(col1name)) AS alias_title FROM favourites; -- returns number of unique items where table header is now called "alias_title"

-- Other functions: AVG, LOWER, MAX, MIN, UPPER, etc.

```


Filters and grouping

```sql
-- WHERE filter
SELECT COUNT(*) from favourites WHERE col1 = 'something' AND col2 = 'something else'; -- returns count of rows where col1 is equal to something and col 2 is equal to something else

-- LIKE 


-- ORDER BY


-- GROUP BY
SELECT col1, count(*) FROM favourites GROUP BY col1; -- Returns table with col1 items and their number of appearance in the second column (pivot table)

-- LIMIT
SELECT col1, count(*) FROM favourites GROUP BY col1 LIMIT 1; -- Returns table with col1 items and their number of appearance in the second column (pivot table) but only one row (limit results to 1 result)

```


Writing to and deleting from the database

```sql
-- UPDATE
UPDATE favorites SET col1 = 'some new value' WHERE col1 = 'some existing value'; -- this will overwrite all col1 items with some existing value to some new value

-- DELETE
DELETE FROM favorites WHERE col1 = 'some value'; -- this will delete all rows where col1 is some value
```

## SCHEMAS
```sql
.schema -- this will return database schema showing all commands executed for creating tables

```

## Data types (SQL lite)
BLOB - binary large objects (1s and 0)
INTEGER - numbers
NUMERIC - specially formatted numbers (date for example)
REAL - float
TEXT - strings


## Keys
Primary key - unique identifier for the database
Foreign key - foreing key is the reference to some other table column name

Both are used for creating realationships.


## Nesting queries
Examples on imdb database
```sql
SELECT title FROM shows WHERE id IN (SELECT show_id FROM genres WHERE genre = 'comedy'); -- returns names of comedies

SELECT title from shows WHERE id IN (SELECT show_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Steve Carell')) ORDER BY title; -- returns name of shows with Steve Carell ordered alphabetically by title
```

## Joins
Joins multiple tables.

Examples on imdb database
```sql
SELECT * FROM shows JOIN genres ON shows.id = genres.show_id; -- create new table from two tables where data is looked up and joined on the basis of of shows.id and genres-show_id (same id, in one table is primary key in other is foreign key)

SELECT title FROM people
  JOIN stars ON people.id = stars.person_id
  JOIN shows ON stars.show_id = shows.id
  WHERE name = 'Steve Carell';
  -- This joins three tables on the basis people ids and filters it by name Steve Carell
```

## Indexes
Tables can be indexed to perform better with queries. Tradeoff more memory usage.

Creating indexes
```sql
CREATE INDEX title_index ON shows (title); 
-- this creates a B-tree datastructure. Similar to binary tree, but with more that two childs in a tree (upside down tree, from root downwards)
-- improves search time drastically
```


## Python Libriaries for SQL

Here they offer cs50 variant needed for problem set solving.

```python
from cs50 import SQL

# Opening db file
db = SQL("sqlite:///favorites.db")

# Ask user a question
favorite = input("Favorite: ")

# Select all rows in database where problem is equal to the favorite
# This returns list of dictionaries

# rows = db.execute(f"SELECT * FROM favorites WHERE problem = {favorite}") - not a good way, we use special placeholders here (?), then we plug in variable. This prevents sql injection attacks by escaping any problematic symbols (such as comments or single qoutes) in the user input
rows = db.execute("SELECT * FROM favorites WHERE problem = ?", favorite)

# Loop over rows and access key-value (here we are returning timestamp) of each return
for row in rows:
  print(row["Timestamp"])
```
