

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "display.h"
#include "car.h"
#include "map.h"

using namespace std;
int main() {

	cout << "welcome to car" << endl;


	int angle1 = 180+45;
	int speed1 = 10;

	int angle2 = 180+45;
	int speed2 = 10;

	vectoradjust(&angle1, &speed1, angle2, speed2);

	cout << "angle: " << angle1 << " speed: " << speed1 << endl;
	char name[20] = "firstmap.tmx";
	map first(name);
	int loc = 0;
	cout << first.getwalls()[loc].getdraw()->getsize() << endl;
	for (int i = 0; i < first.getwalls()[loc].getdraw()->getsize();i++) {
		cout << first.getwalls()[loc].getdraw()->getline(i).x1 << ",";
		cout << first.getwalls()[loc].getdraw()->getline(i).y1 << "  ";
		cout << first.getwalls()[loc].getdraw()->getline(i).x2 << ",";
		cout << first.getwalls()[loc].getdraw()->getline(i).y2 << endl;
	}



	system("pause");
	al_init();
	al_init_primitives_addon();

	ALLEGRO_TIMER * timmer;
	ALLEGRO_EVENT_QUEUE * queue;


	display screen = display(800,600,1);
	
	timmer = al_create_timer(1 / 30.0);
	queue = al_create_event_queue();
	al_install_keyboard();
	al_start_timer(timmer);

	al_register_event_source(queue, al_get_display_event_source(screen.gets()));
	al_register_event_source(queue, al_get_timer_event_source(timmer));
	al_register_event_source(queue, al_get_keyboard_event_source());

	car player(200, 150, 40, 70,0);


	bool done = false;
	while (!done) {
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {

			ALLEGRO_KEYBOARD_STATE keys;
			al_get_keyboard_state(&keys);


			if (al_key_down(&keys, ALLEGRO_KEY_A)&& al_key_down(&keys, ALLEGRO_KEY_D)) {
				screen.adjCam(0, 0);
			}
			else if (al_key_down(&keys, ALLEGRO_KEY_A)) {
				screen.adjCam(-10, 0);
			}
			else if (al_key_down(&keys, ALLEGRO_KEY_D)) {
				screen.adjCam(10, 0);
			}

			if (al_key_down(&keys, ALLEGRO_KEY_W) && al_key_down(&keys, ALLEGRO_KEY_S)) {
				screen.adjCam(0, 0);
			}
			else if (al_key_down(&keys, ALLEGRO_KEY_W)) {
				screen.adjCam(0, -10);
			}
			else if (al_key_down(&keys, ALLEGRO_KEY_S)) {
				screen.adjCam(0, 10);
			}

			if (al_key_down(&keys, ALLEGRO_KEY_LEFT)) {
				player.setleft(true);
			}
			else {
				player.setleft(false);
			}

			if (al_key_down(&keys, ALLEGRO_KEY_RIGHT)) {
				player.setright(true);
			}
			else {
				player.setright(false);
			}
			if (al_key_down(&keys, ALLEGRO_KEY_SPACE)) {
				player.setpower(true);
			}
			else {
				player.setpower(false);
			}
			screen.setCam(player.getx()-400,player.gety()-300);
			player.update();

			screen.drawstart();

			for (int i = 0; i < first.getsize(); i++) {
				first.getwalls()[i];
				screen.draw(first.getwalls()[i].getdraw());
			}

			screen.draw(player.drawingbody());
			screen.drawview();
			al_flip_display();


		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
	}
	return 0;
}