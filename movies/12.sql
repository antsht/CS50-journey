SELECT title FROM movies
WHERE id IN
(SELECT movie_id FROM stars
JOIN people ON people.id = stars.person_id
WHERE name = 'Bradley Cooper')
AND id IN
(SELECT movie_id FROM stars
JOIN people ON people.id = stars.person_id
WHERE name = 'Jennifer Lawrence');
