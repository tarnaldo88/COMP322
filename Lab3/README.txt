LAB3 README:

signals array: Set up an array containing the 31 possible signals from SIGHUP to SIGSYS
		**Update** : removed SIG from list as program arguments will not have them and makes easier to compar
CATCHER(): function to determine which of the signals will be caught, loops through the library of signals and compares them to 
	   to the program arguments given in argv.
	   Program then registers handlers for each signal to be caught, and loops continuously with pause() inside until
	   three SIGTERMS are caught consecutively. 
	   Then prints how many signals were caught.
SIGHAND() : function to handle the signals caught, if SIGTERM is caught it increments a counter, and if anything else is caught
	    it resets back to zero, fucntionally similar to regular expression (a + b)*aaa
	    Prints out which signal it was caught and the at which it was caught