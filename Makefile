.POSIX:
PREFIX = /usr/local

.SUFFIXES:
all:
	# cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic src/midi/*.c src/synth/*.c src/utils/*.c src/main.c -o "hog"
	cc -lsndio -lm -O3 --std=c11 -Wall -Wextra -Wno-missing-field-initializers -pedantic src/audio/*.c src/midi/*.c src/synth/*.c src/io/*.c src/main.c -o "sow"
quick:
	cc -lsndio -lm --std=c11 src/audio/*.c src/midi/*.c src/synth/*.c src/io/*.c src/main.c -o "sow"
	./sow
	rm sow
test:
	# cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -DTEST src/midi/*.c src/synth/*.c src/utils/*.c src/tests/*.c src/main.c -o "hog_test"
	cc -O3 -lsndio -lm --std=c11 -Wall -Wextra -Wno-missing-field-initializers -pedantic -DTEST src/audio/*.c src/midi/*.c src/synth/*.c src/io/*.c src/tests/*.c src/main.c -o "sow_test"
	./sow_test
	rm sow_test
