SELECT count(*) FROM movies WHERE id in (SELECT movie_id FROM ratings WHERE rating = 10);
