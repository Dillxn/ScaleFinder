/* ScaleFinder.cpp : Return scales including given set of chords;
   Dillon Riecke     Return scales including given set of notes.

                     executeQuery() & sql includes boiler plate code from https://docs.marklogic.com/guide/messages/SQL-en
*/

#include <stdlib.h>
#include <iostream>

/* Include mysql & cppconn headers */
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

/* Prototypes */
string sharpFlat(string name);
string executeQuery(string query, bool spaces = true);

int main(void)
{
    /* input         - user input from the console
       chordName     - name of a given chord for processing
       noteName      - name of a given note for processing
       alternateName - Equivalent name for given chord or note, eg. Eb = D#
       query         - string built for use in query sent to MariaDB
       queryResponse - MariaDB's output after queried

       noteNameCount  - used in our query building algorithm to determine
                        if 'AND' needs to be appended before a parenthetical
                        in our selection clause
       chordNameCount - same function as noteNameCount in its respective loop
    */
    string input, chordName, noteName, alternateName, query, queryResponse;
    int noteNameCount, chordNameCount;

    cout << "Welcome to ScaleFinder. Would you prefer to identify scales containing given notes or chords?" << endl;
    cin >> input;

    /* Main program loop */
    while (input != "exit") {

        /* Format query for chords */
        if (input == "chords") {

            cout << "What chords would you like to include? (space delineated)" << endl;

            /* using ignore() and getline() to retrieve more than just the first word for cin,
               in case multiple chords are listed */
            cin.ignore();
            getline(cin, input);
            
            /* Build query. We do this by looping over the characters of the input and
               identifying chord names that need to be included in our SELECT */
            query = "";
            chordName = "";
            alternateName = "";
            chordNameCount = 0;
            for (int i = 0; i < input.length() + 1; i++) {

                /* When we reach a space or the EOL add last non-empty chord name constructed */
                if ((i == input.length() || input[i] == ' ') && chordName != "") {

                    /* Add AND if we've already added at least one chord name */
                    query += (chordNameCount > 0) ? " AND " : "";

                    /* In music theory, the same chord can have multiple names.
                       eg. A#m is represented as Bbm in the Ab scale. 
                       If we find an alternate name for a given chord, we want to extend
                       our query to search for it under its alternate name, too. */
                    alternateName = sharpFlat(chordName);
                    query += (alternateName != "") ? "(" : "";

                    query +=  "(i = '" + chordName +
                        "' OR ii = '" + chordName +
                        "' OR iii = '" + chordName +
                        "' OR iv = '" + chordName +
                        "' OR v = '" + chordName +
                        "' OR vi = '" + chordName +
                        "' OR vii = '" + chordName + "')";
                    
                    if (alternateName != "") {
                        query += " OR (i = '" + alternateName +
                            "' OR ii = '" + alternateName +
                            "' OR iii = '" + alternateName +
                            "' OR iv = '" + alternateName +
                            "' OR v = '" + alternateName +
                            "' OR vi = '" + alternateName +
                            "' OR vii = '" + alternateName + "')" +
                            ")";
                    }

                    chordNameCount++;
                    chordName = "";
                    alternateName = "";
                }
                /* Else if the character is not a space, add the character to the current
                   chord name */
                else {
                    chordName += input[i];
                }
            }
            query += ";";

            /* We want to retrieve not just the major scale names, but also
               their relative minor scale names (same as the vi chord name) */
            queryResponse = executeQuery("SELECT scaleName FROM scale WHERE " + query) +
                executeQuery("SELECT vi FROM scale WHERE " + query);

            if (queryResponse != "") {
                cout << "is found in the scales:\n" + queryResponse;
            }
            else {
                cout << "is not contained in any scale.\n";
            }
            
        }
        /* Format query for notes */
        else if (input == "notes") {

            cout << "What notes would you like to include? (space delineated)" << endl;

            /* using ignore() and getline() to retrieve more than just the first word for cin,
               in case multiple notes are listed */
            cin.ignore();
            getline(cin, input);

            /* Build query. This time we have a nested loop. First we loop over the note names
               the user has provided. */
            query = "";
            noteName = "";
            alternateName = "";
            noteNameCount = 0;
            for (int i = 0; i < input.length() + 1; i++) {

                /* When we reach a space or the EOL, process last non-empty note name constructed */
                if ((i == input.length() || input[i] == ' ') && noteName != "") {

                    /* Add AND if we've already added at least one note name.
                       We use AND here to make sure every note has a chord
                       representing it in the returned scale */
                    query += (noteNameCount > 0) ? " AND " : "";
                    
                    /* Find all the chords containing the given note */
                    queryResponse = executeQuery("SELECT chordName FROM chord WHERE first = '" + noteName +
                        "' OR  second = '" + noteName +
                        "' OR  third = '" + noteName + "';");
                    /* In music theory, the same note can have multiple names, eg. Eb = D#.
                       If we find an alternate name for a given note, we want to retrieve
                       chords containing its alias, too. */
                    alternateName = sharpFlat(noteName);
                    queryResponse += executeQuery("SELECT chordName FROM chord WHERE first = '" + alternateName +
                        "' OR  second = '" + alternateName +
                        "' OR  third = '" + alternateName + "';");

                    /* Loop over the chords containing our given note */
                    chordName = "";
                    query += "(";
                    chordNameCount = 0;
                    for (int x = 0; x < queryResponse.length() + 1; x++) {

                        /* For each chord in the queryResponse, construct a portion
                           of the WHERE clause to select scales that contain the given chord */
                        if ((x == queryResponse.length() || queryResponse[x] == ' ') && chordName != "") {
                            /* We use OR here because we only need to ensure one of the chords that 
                               contains the given note is in the returned scale */
                            query += (chordNameCount > 0) ? " OR " : "";

                            alternateName = sharpFlat(chordName);
                            query += (alternateName != "") ? "(" : "";

                            query += "(i = '" + chordName +
                                "' OR ii = '" + chordName +
                                "' OR iii = '" + chordName +
                                "' OR iv = '" + chordName +
                                "' OR v = '" + chordName +
                                "' OR vi = '" + chordName +
                                "' OR vii = '" + chordName + "')";

                            if (alternateName != "") {
                                query += " OR (i = '" + alternateName +
                                    "' OR ii = '" + alternateName +
                                    "' OR iii = '" + alternateName +
                                    "' OR iv = '" + alternateName +
                                    "' OR v = '" + alternateName +
                                    "' OR vi = '" + alternateName +
                                    "' OR vii = '" + alternateName + "')" +
                                    ")";
                            }

                            chordNameCount++;
                            chordName = "";
                            alternateName = "";
                        }
                        else {
                            chordName += queryResponse[x];
                        }
                    }
                    query += ") ";

                    noteNameCount++;
                    noteName = "";
                    alternateName = "";
                }
                /* Else if the character is not a space, add the character to the current
                   chord name */
                else {
                    noteName += input[i];
                }
            }
            query += ";";

            /* We want to retrieve not just the major scale names, but also
               their relative minor scale names (same as the vi chord name) */
            queryResponse = executeQuery("SELECT scaleName FROM scale WHERE " + query) +
                executeQuery("SELECT vi FROM scale WHERE " + query);

            if (queryResponse != "") {
                cout << "is found in the scales:\n" + queryResponse << endl;
            }
            else {
                cout << "is not contained in any scale." << endl;
            }

        }
        else {
            cout << "Input not recognized. Try 'chords' 'notes' or 'exit'" << endl;
        }

        cout << "\nAnything else?" << endl;
        cin >> input;
    }
    
    return EXIT_SUCCESS;
}

/* sharpFlat() - find equivalent chord or note for names containing a sharp or a flat */
string sharpFlat(string name) {
    string alternateName = "";

    alternateName += executeQuery("SELECT sharp FROM sharp_flat WHERE flat = '" + name + "';", false);
    alternateName += executeQuery("SELECT flat FROM sharp_flat WHERE sharp = '" + name + "';", false);

    return alternateName;
}

/* executeQuery() - slightly modified bioler plate code to connect to our DB and execute a query, abstracted to a function */
string executeQuery(string query, bool spaces) {

    string queryResponse = "";

    try {
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        /* Connect to the scaleFinder database */
        con->setSchema("scaleFinder");

        stmt = con->createStatement();
        res = stmt->executeQuery(query);
        while (res->next()) {
            /* Access column data by numeric offset, 1 is the first column */
            queryResponse += res->getString(1) + (spaces ? " " : "");
        }
        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        /* cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl; */
    }

    return queryResponse;
}