/*
Simple MongoDB query for the imdb actor database using refactored 
sample code from Allen Downeys version of tutorial.c 

Hw03 March 2014

Rahil Dedhia, Deborah Hellen, Charlene Lee, Aidan McLaughlin
*/

#include <stdio.h>
#include "mongo.h"
#include <time.h>

static void simple_query( mongo *conn ) 
/*Function that queries the database using a bson object 
given a current database connection *conn
This function is a modified version of the tutorial_simple_query from tutorial.c*/
{
  bson query[1];
  mongo_cursor cursor[1];

  bson_init( query );
  bson_append_string( query, "name", "Bacon, Kevin (I)" );
  bson_finish( query );

  mongo_cursor_init( cursor, conn, "imdb.actor" );
  mongo_cursor_set_query( cursor, query );

  while( mongo_cursor_next( cursor ) == MONGO_OK ) {
    bson_iterator iterator[1];
    if ( bson_find( iterator, mongo_cursor_bson( cursor ), "name" )) {
        printf( "name: %s\n", bson_iterator_string( iterator ) );
    }
    else {
    }
  }
  bson_destroy( query );
  mongo_cursor_destroy( cursor );
}


int main() 
/*Connects to mongoDB, and calls the simple_query function.
Then calculates the amount of time needed for the query
to run.*/
{
  mongo conn[1];
  int status = mongo_client( conn, "127.0.0.1", 27017 );

  if( status != MONGO_OK ) {
      switch ( conn->err ) {
        case MONGO_CONN_NO_SOCKET:  printf( "no socket\n" ); return 1;
        case MONGO_CONN_FAIL:       printf( "connection failed\n" ); return 1;
        case MONGO_CONN_NOT_MASTER: printf( "not master\n" ); return 1;
      }
  }
  time_t start_t, end_t;
  double diff_t;
  time(&start_t);
  
  simple_query(conn);
  
  time(&end_t);
  //Computes the time needed to run simple_query
  diff_t = difftime(end_t, start_t);

  printf("Execution time = %f\n", diff_t);
  mongo_destroy( conn );
  return 0;
}