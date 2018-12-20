

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
	int vx = 6;
	int vy = -2;
	cout << endl;
	vectorbounce(&vx,&vy, line(0, 0, 4, 2).getslope());
	cout << vx << "," << vy << endl;


	system("pause");
	al_init();
	al_init_primitives_addon();

	ALLEGRO_TIMER * timmer;
	ALLEGRO_EVENT_QUEUE * queue;


	display screen = display(400,300,2);
	
	timmer = al_create_timer(1 / 30.0);
	queue = al_create_event_queue();
	al_install_keyboard();
	al_start_timer(timmer);

	al_register_event_source(queue, al_get_display_event_source(screen.gets()));
	al_register_event_source(queue, al_get_timer_event_source(timmer));
	al_register_event_source(queue, al_get_keyboard_event_source());

	car player(200, 150, 20, 35,0);
	player.setx(first.start[0]);
	player.sety(first.start[1]);

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
			screen.setCam(player.getx()-200,player.gety()-150);
			player.rotationupdate();
			for (int i = 0; i < first.getsize(); i++) {
				if (first.getwalls()[i].circularcolide(player.getc())) {
					if (first.getwalls()[i].colides(player.getc())) {
						player.collisionrotation(&first.getwalls()[i]);
					}
				}
			}
			player.setonwall(false);
			for (int i = 0; i < first.getsize(); i++) {
				if (first.getwalls()[i].circularcolide(player.getf())) {
					if (first.getwalls()[i].colides(player.getf())) {
						player.setonwall(true);
						break;
					}
				}
			}




			player.update();

			line edge;
			bool colide = false;
			for (int i = 0; i < first.getsize(); i++) {
				if (first.getwalls()[i].circularcolide(player.getc())) {
					if (first.getwalls()[i].colides(player.getc())) {
						colide = true;
						edge = player.getc()->getline(&first.getwalls()[i]);
						player.collisionmove(&first.getwalls()[i]);
					}
				}
			}
			if (colide) {
				//player.changevelocity(edge);
			}
			screen.drawstart();

			for (int i = 0; i < first.getsize(); i++) {
				screen.draw(first.getwalls()[i].getdraw());
			}
			screen.draw(player.drawingflame());
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