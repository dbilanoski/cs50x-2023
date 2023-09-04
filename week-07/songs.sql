SELECT name FROM songs;
SELECT name FROM songs ORDER BY tempo;
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;
SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;
SELECT AVG(energy) FROM songs;
SELECT name FROM songs WHERE artist_ID = (SELECT id FROM artists WHERE name = "Post Malone");
SELECT AVG(energy) FROM songs WHERE artist_ID = (SELECT id FROM artists WHERE name = "Drake");
SELECT name FROM songs WHERE name LIKE '%feat.%';

/* 

ANSWERS:

1. So by looking at averages of those values from the assignment speculation (below)

Average energy: 0.65906
Average valence: 0.484443
Average daceability: 0.71646

looks like it might be Purple (Purple: This aura color pairs well with passionate music listeners. Purple auras tune in to get amped up, entertained, and moving while they navigate the twists and turns of their day.)

Since I am not sure what the "valence" refers to, I am not able to speculate abot finer details of this but just by the averages, I would say movemenet, energy, good vibes but not too many lingering over emotions or meaning.

2. Criteria wise, more criteria should be taken into account to make a more precise guess for someones musical taste.
Calculation wise, it should consider peaks, repetion of those peak values and chaing repetition of those, not just averages. Then correlate those with song's genres, speechines, loudness etc to see what are the edges of someones taste.

*/