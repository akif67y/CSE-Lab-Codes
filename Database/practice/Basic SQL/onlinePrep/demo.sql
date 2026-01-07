-- Movie Management Database Schema for Oracle 19c
-- Drop tables if they exist (in reverse order of dependencies)
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE SOCIAL_MEDIA_SHARES CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE AI_RECOMMENDATIONS CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE RATINGS CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE REVIEWS CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE WATCHLIST CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE WATCHED_MOVIES CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE MOVIE_GENRES CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE FOLLOWERS CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE GENRES CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE MOVIES CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP TABLE USERS CASCADE CONSTRAINTS';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/

-- Drop sequences if they exist
BEGIN
   EXECUTE IMMEDIATE 'DROP SEQUENCE users_seq';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP SEQUENCE movies_seq';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP SEQUENCE genres_seq';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP SEQUENCE watched_movies_seq';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP SEQUENCE watchlist_seq';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP SEQUENCE reviews_seq';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP SEQUENCE ratings_seq';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP SEQUENCE ai_recommendations_seq';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/
BEGIN
   EXECUTE IMMEDIATE 'DROP SEQUENCE social_shares_seq';
EXCEPTION
   WHEN OTHERS THEN NULL;
END;
/

-- Create sequences for auto-increment
CREATE SEQUENCE users_seq START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE movies_seq START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE genres_seq START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE watched_movies_seq START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE watchlist_seq START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE reviews_seq START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE ratings_seq START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE ai_recommendations_seq START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE social_shares_seq START WITH 1 INCREMENT BY 1;

-- Create USERS table
CREATE TABLE USERS (
    user_id NUMBER PRIMARY KEY,
    username VARCHAR2(50) NOT NULL UNIQUE,
    email VARCHAR2(100) NOT NULL UNIQUE,
    password_hash VARCHAR2(255) NOT NULL,
    display_name VARCHAR2(100),
    bio CLOB,
    profile_picture VARCHAR2(255),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    last_login TIMESTAMP
);

-- Create trigger for USERS auto-increment
CREATE OR REPLACE TRIGGER users_bir 
BEFORE INSERT ON USERS 
FOR EACH ROW
BEGIN
  IF :NEW.user_id IS NULL THEN
    SELECT users_seq.NEXTVAL INTO :NEW.user_id FROM dual;
  END IF;
END;
/

-- Create MOVIES table
CREATE TABLE MOVIES (
    movie_id NUMBER PRIMARY KEY,
    title VARCHAR2(200) NOT NULL,
    release_year NUMBER(4),
    director VARCHAR2(100),
    duration_minutes NUMBER,
    synopsis CLOB,
    poster_url VARCHAR2(255),
    trailer_url VARCHAR2(255),
    imdb_rating NUMBER(3,1),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT chk_release_year CHECK (release_year >= 1800 AND release_year <= 2100),
    CONSTRAINT chk_duration CHECK (duration_minutes > 0),
    CONSTRAINT chk_rating CHECK (imdb_rating >= 0 AND imdb_rating <= 10)
);

-- Create trigger for MOVIES auto-increment
CREATE OR REPLACE TRIGGER movies_bir 
BEFORE INSERT ON MOVIES 
FOR EACH ROW
BEGIN
  IF :NEW.movie_id IS NULL THEN
    SELECT movies_seq.NEXTVAL INTO :NEW.movie_id FROM dual;
  END IF;
END;
/

-- Create GENRES table
CREATE TABLE GENRES (
    genre_id NUMBER PRIMARY KEY,
    genre_name VARCHAR2(50) NOT NULL UNIQUE,
    description CLOB
);

-- Create trigger for GENRES auto-increment
CREATE OR REPLACE TRIGGER genres_bir 
BEFORE INSERT ON GENRES 
FOR EACH ROW
BEGIN
  IF :NEW.genre_id IS NULL THEN
    SELECT genres_seq.NEXTVAL INTO :NEW.genre_id FROM dual;
  END IF;
END;
/

-- Create MOVIE_GENRES junction table
CREATE TABLE MOVIE_GENRES (
    movie_id NUMBER,
    genre_id NUMBER,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_movie_genres PRIMARY KEY (movie_id, genre_id),
    CONSTRAINT fk_mg_movie FOREIGN KEY (movie_id) REFERENCES MOVIES(movie_id) ON DELETE CASCADE,
    CONSTRAINT fk_mg_genre FOREIGN KEY (genre_id) REFERENCES GENRES(genre_id) ON DELETE CASCADE
);

-- Create FOLLOWERS table (self-referential for user connections)
CREATE TABLE FOLLOWERS (
    follower_id NUMBER,
    following_id NUMBER,
    followed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_followers PRIMARY KEY (follower_id, following_id),
    CONSTRAINT fk_follower FOREIGN KEY (follower_id) REFERENCES USERS(user_id) ON DELETE CASCADE,
    CONSTRAINT fk_following FOREIGN KEY (following_id) REFERENCES USERS(user_id) ON DELETE CASCADE,
    CONSTRAINT chk_no_self_follow CHECK (follower_id != following_id)
);

-- Create WATCHED_MOVIES table
CREATE TABLE WATCHED_MOVIES (
    watch_id NUMBER PRIMARY KEY,
    user_id NUMBER NOT NULL,
    movie_id NUMBER NOT NULL,
    watch_date DATE NOT NULL,
    personal_notes CLOB,
    rewatch NUMBER(1) DEFAULT 0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT fk_watched_user FOREIGN KEY (user_id) REFERENCES USERS(user_id) ON DELETE CASCADE,
    CONSTRAINT fk_watched_movie FOREIGN KEY (movie_id) REFERENCES MOVIES(movie_id) ON DELETE CASCADE,
    CONSTRAINT uk_user_movie_date UNIQUE (user_id, movie_id, watch_date),
    CONSTRAINT chk_rewatch CHECK (rewatch IN (0, 1))
);

-- Create trigger for WATCHED_MOVIES auto-increment
CREATE OR REPLACE TRIGGER watched_movies_bir 
BEFORE INSERT ON WATCHED_MOVIES 
FOR EACH ROW
BEGIN
  IF :NEW.watch_id IS NULL THEN
    SELECT watched_movies_seq.NEXTVAL INTO :NEW.watch_id FROM dual;
  END IF;
END;
/

-- Create WATCHLIST table
CREATE TABLE WATCHLIST (
    watchlist_id NUMBER PRIMARY KEY,
    user_id NUMBER NOT NULL,
    movie_id NUMBER NOT NULL,
    priority NUMBER DEFAULT 0,
    added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    notes CLOB,
    CONSTRAINT fk_watchlist_user FOREIGN KEY (user_id) REFERENCES USERS(user_id) ON DELETE CASCADE,
    CONSTRAINT fk_watchlist_movie FOREIGN KEY (movie_id) REFERENCES MOVIES(movie_id) ON DELETE CASCADE,
    CONSTRAINT uk_user_movie_watchlist UNIQUE (user_id, movie_id),
    CONSTRAINT chk_priority CHECK (priority >= 0 AND priority <= 10)
);

-- Create trigger for WATCHLIST auto-increment
CREATE OR REPLACE TRIGGER watchlist_bir 
BEFORE INSERT ON WATCHLIST 
FOR EACH ROW
BEGIN
  IF :NEW.watchlist_id IS NULL THEN
    SELECT watchlist_seq.NEXTVAL INTO :NEW.watchlist_id FROM dual;
  END IF;
END;
/

-- Create REVIEWS table
CREATE TABLE REVIEWS (
    review_id NUMBER PRIMARY KEY,
    user_id NUMBER NOT NULL,
    movie_id NUMBER NOT NULL,
    rating NUMBER(2,1),
    review_text CLOB NOT NULL,
    likes_count NUMBER DEFAULT 0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT fk_review_user FOREIGN KEY (user_id) REFERENCES USERS(user_id) ON DELETE CASCADE,
    CONSTRAINT fk_review_movie FOREIGN KEY (movie_id) REFERENCES MOVIES(movie_id) ON DELETE CASCADE,
    CONSTRAINT uk_user_movie_review UNIQUE (user_id, movie_id),
    CONSTRAINT chk_review_rating CHECK (rating >= 0 AND rating <= 10),
    CONSTRAINT chk_likes_count CHECK (likes_count >= 0)
);

-- Create trigger for REVIEWS auto-increment
CREATE OR REPLACE TRIGGER reviews_bir 
BEFORE INSERT ON REVIEWS 
FOR EACH ROW
BEGIN
  IF :NEW.review_id IS NULL THEN
    SELECT reviews_seq.NEXTVAL INTO :NEW.review_id FROM dual;
  END IF;
END;
/

-- Create trigger for REVIEWS updated_at
CREATE OR REPLACE TRIGGER reviews_bur 
BEFORE UPDATE ON REVIEWS 
FOR EACH ROW
BEGIN
  :NEW.updated_at := CURRENT_TIMESTAMP;
END;
/

-- Create RATINGS table
CREATE TABLE RATINGS (
    rating_id NUMBER PRIMARY KEY,
    user_id NUMBER NOT NULL,
    movie_id NUMBER NOT NULL,
    rating_value NUMBER(2,1) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT fk_rating_user FOREIGN KEY (user_id) REFERENCES USERS(user_id) ON DELETE CASCADE,
    CONSTRAINT fk_rating_movie FOREIGN KEY (movie_id) REFERENCES MOVIES(movie_id) ON DELETE CASCADE,
    CONSTRAINT uk_user_movie_rating UNIQUE (user_id, movie_id),
    CONSTRAINT chk_rating_value CHECK (rating_value >= 0 AND rating_value <= 10)
);

-- Create trigger for RATINGS auto-increment
CREATE OR REPLACE TRIGGER ratings_bir 
BEFORE INSERT ON RATINGS 
FOR EACH ROW
BEGIN
  IF :NEW.rating_id IS NULL THEN
    SELECT ratings_seq.NEXTVAL INTO :NEW.rating_id FROM dual;
  END IF;
END;
/

-- Create AI_RECOMMENDATIONS table
CREATE TABLE AI_RECOMMENDATIONS (
    recommendation_id NUMBER PRIMARY KEY,
    user_id NUMBER NOT NULL,
    movie_id NUMBER NOT NULL,
    mood VARCHAR2(50),
    confidence_score NUMBER(3,2),
    reason CLOB,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT fk_ai_rec_user FOREIGN KEY (user_id) REFERENCES USERS(user_id) ON DELETE CASCADE,
    CONSTRAINT fk_ai_rec_movie FOREIGN KEY (movie_id) REFERENCES MOVIES(movie_id) ON DELETE CASCADE,
    CONSTRAINT chk_confidence CHECK (confidence_score >= 0 AND confidence_score <= 1)
);

-- Create trigger for AI_RECOMMENDATIONS auto-increment
CREATE OR REPLACE TRIGGER ai_recommendations_bir 
BEFORE INSERT ON AI_RECOMMENDATIONS 
FOR EACH ROW
BEGIN
  IF :NEW.recommendation_id IS NULL THEN
    SELECT ai_recommendations_seq.NEXTVAL INTO :NEW.recommendation_id FROM dual;
  END IF;
END;
/

-- Create SOCIAL_MEDIA_SHARES table
CREATE TABLE SOCIAL_MEDIA_SHARES (
    share_id NUMBER PRIMARY KEY,
    user_id NUMBER NOT NULL,
    review_id NUMBER NOT NULL,
    platform VARCHAR2(50) NOT NULL,
    share_url VARCHAR2(255),
    shared_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT fk_share_user FOREIGN KEY (user_id) REFERENCES USERS(user_id) ON DELETE CASCADE,
    CONSTRAINT fk_share_review FOREIGN KEY (review_id) REFERENCES REVIEWS(review_id) ON DELETE CASCADE
);

-- Create trigger for SOCIAL_MEDIA_SHARES auto-increment
CREATE OR REPLACE TRIGGER social_shares_bir 
BEFORE INSERT ON SOCIAL_MEDIA_SHARES 
FOR EACH ROW
BEGIN
  IF :NEW.share_id IS NULL THEN
    SELECT social_shares_seq.NEXTVAL INTO :NEW.share_id FROM dual;
  END IF;
END;
/

-- Create indexes for better query performance
CREATE INDEX idx_movies_title ON MOVIES(title);
CREATE INDEX idx_movies_release_year ON MOVIES(release_year);
CREATE INDEX idx_movies_director ON MOVIES(director);
CREATE INDEX idx_watched_movies_user ON WATCHED_MOVIES(user_id);
CREATE INDEX idx_watched_movies_movie ON WATCHED_MOVIES(movie_id);
CREATE INDEX idx_watched_movies_date ON WATCHED_MOVIES(watch_date);
CREATE INDEX idx_watchlist_user ON WATCHLIST(user_id);
CREATE INDEX idx_reviews_user ON REVIEWS(user_id);
CREATE INDEX idx_reviews_movie ON REVIEWS(movie_id);
CREATE INDEX idx_ratings_user ON RATINGS(user_id);
CREATE INDEX idx_ratings_movie ON RATINGS(movie_id);
CREATE INDEX idx_ai_recommendations_user ON AI_RECOMMENDATIONS(user_id);
CREATE INDEX idx_social_shares_user ON SOCIAL_MEDIA_SHARES(user_id);

-- Insert sample genres
INSERT INTO GENRES (genre_name, description) VALUES ('Action', 'High-energy films with physical stunts and chases');
INSERT INTO GENRES (genre_name, description) VALUES ('Drama', 'Serious, plot-driven films');
INSERT INTO GENRES (genre_name, description) VALUES ('Comedy', 'Humorous films intended to make audience laugh');
INSERT INTO GENRES (genre_name, description) VALUES ('Horror', 'Films designed to frighten and invoke fear');
INSERT INTO GENRES (genre_name, description) VALUES ('Science Fiction', 'Films with futuristic or scientific themes');
INSERT INTO GENRES (genre_name, description) VALUES ('Romance', 'Films focused on love and relationships');
INSERT INTO GENRES (genre_name, description) VALUES ('Thriller', 'Suspenseful films with tension and excitement');
INSERT INTO GENRES (genre_name, description) VALUES ('Documentary', 'Non-fiction films about real events');
INSERT INTO GENRES (genre_name, description) VALUES ('Animation', 'Films created using animated techniques');
INSERT INTO GENRES (genre_name, description) VALUES ('Fantasy', 'Films with magical or supernatural elements');

COMMIT;

-- Display success message
SELECT 'Database schema created successfully for Oracle 19c!' AS Status FROM dual;