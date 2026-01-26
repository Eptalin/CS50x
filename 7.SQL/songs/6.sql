SELECT name 
  FROM songs
 WHERE artist_id = (
    SELECT id 
      FROM artists
     WHERE name = 'Post Malone'
);

SELECT s.name 
  FROM songs AS s
  JOIN artists AS a on s.artist_id = a.id
 WHERE a.name = 'Post Malone';