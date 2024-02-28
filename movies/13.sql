SELECT name FROM people
WHERE id IN
(SELECT person_id FROM stars WHERE movie_id IN
(SELECT movie_id FROM stars
JOIN people ON people.id = stars.person_id
WHERE name = 'Kevin Bacon' and birth = 1958))
AND name <> 'Kevin Bacon';

