#include "mario_bros.hpp"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <sstream>
#include "global_dec.hpp"
#include "goomba.hpp"
#include "fonts.hpp"
#include "coin.hpp"
#include "images.hpp"
#include "keys.hpp"
#include "map.hpp"
#include "sounds.hpp"
#include "mario.hpp"
#include "wipe.hpp"




void Mario::game_title() noexcept {
  if (IMG_Init(IMG_INIT_PNG)!=IMG_INIT_PNG){
    std::cerr<<"Failed to initialize SDL_image";
    abort;
  }
  SDL_Surface * image;
  
  //SDL_SetRenderDrawColor(renderer_, 18, 187, 224, 0);
  //SDL_RenderClear(renderer_);

  const Point title_pos = Point{220, 160};
  const Point p1_mode_pos = Point{270, 300};
  const Point vs_mode_pos = Point{270, 350};
  const Point hp_mode_pos = Point{100, 250};
  const char *title_str = " ";
  const char *p1_mode_str = "Play as Mario";
  const char *vs_mode_str = "Play with Luigi";
  const char *hp_mode_str="don't know how to play press H";
  const SDL_Rect p1_str_dst = {250, 298, 250, 26};
  const SDL_Rect vs_str_dst = {250, 348, 250, 26};
  const SDL_Rect hp_str_dst = {250, 398, 250, 26};
  switch (game_count_) {
    case 0: {
      wipe_->set_wipe_in();
      wipe_->draw(screen::width);
      ++game_count_;
      break;
    }
    case 1: {
      draw_text(font_size::x36, rgb::black, title_pos, title_str);
      wipe_->draw(screen::width);
      if (wipe_->update()) {
        ++game_count_;
      }
      break;
    }
    case 2: {
      SDL_Surface * image=IMG_Load("resources/graphics/mario-intro.png");
  	if (image==NULL){
  		std::cerr<<"unable to load image";
  	}
  	SDL_Texture * texture=SDL_CreateTextureFromSurface(renderer_,image);
  	SDL_RenderCopy(renderer_, texture, NULL, NULL);
  	SDL_RenderPresent(renderer_);
      draw_text(font_size::x36, rgb::black, title_pos, title_str);
      if (blink_count_ < 30) {
        draw_text(font_size::x16, rgb::black, Point{205, 300},
                  "Press SPACE key for Menu");
        ++blink_count_;
      } else if (blink_count_ < 60) {
        ++blink_count_;
      } else {
        blink_count_ = 0;
      }

      if (input_manager_->edge_key_p(player_type::p1, input_device::x)
          || input_manager_->edge_key_p(player_type::p2, input_device::x)
          || input_manager_->edge_key_p(player_type::p1, input_device::space)
          || input_manager_->edge_key_p(player_type::p2, input_device::space)) {
        ++game_count_;
        blink_count_ = 0;
      }
      break;
    }
    case 3: {
      draw_text(font_size::x36, rgb::black, title_pos, title_str);
      if (!input_manager_->press_key_p(player_type::p1, input_device::x)
          && !input_manager_->press_key_p(player_type::p2, input_device::x)
          && !input_manager_->press_key_p(player_type::p1, input_device::space)
          && !input_manager_->press_key_p(player_type::p2, input_device::space)) {
        ++game_count_;
      }
      break;
    }
    case 4: {
      draw_text(font_size::x36, rgb::black, title_pos, title_str);

      switch (game_mode_) {
        case game_mode::single: {
          image=IMG_Load("resources/graphics/mario-intro.png");
          if (image==NULL){
  		std::cerr<<"unable to load image";
  	  }
  	  SDL_Texture * texture=SDL_CreateTextureFromSurface(renderer_,image);
  	  SDL_RenderCopy(renderer_, texture, NULL, NULL);
  	  SDL_RenderPresent(renderer_);
          SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
          SDL_RenderFillRect(renderer_, &p1_str_dst);
          draw_text(font_size::x16, rgb::white, p1_mode_pos, p1_mode_str);
          draw_text(font_size::x16, rgb::black, vs_mode_pos, vs_mode_str);
          draw_text(font_size::x16, rgb::black, hp_mode_pos, hp_mode_str);
          break;
        }
        case game_mode::battle: {
          image=IMG_Load("resources/graphics/mario-intro.png");
          if (image==NULL){
  		std::cerr<<"unable to load image";
  	  }
  	  SDL_Texture * texture=SDL_CreateTextureFromSurface(renderer_,image);
  	  SDL_RenderCopy(renderer_, texture, NULL, NULL);
  	  SDL_RenderPresent(renderer_);
          SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
          SDL_RenderFillRect(renderer_, &vs_str_dst);
          draw_text(font_size::x16, rgb::black, p1_mode_pos, p1_mode_str);
          draw_text(font_size::x16, rgb::white, vs_mode_pos, vs_mode_str);
          draw_text(font_size::x16, rgb::black, hp_mode_pos, hp_mode_str);
          break;
        }
        case game_mode::help: {
        	image=IMG_Load("resources/graphics/mario-instruc.png");
        	if (image==NULL){
  			std::cerr<<"unable to load image";
  		}
  		SDL_Texture * texture=SDL_CreateTextureFromSurface(renderer_,image);
  		SDL_RenderCopy(renderer_, texture, NULL, NULL);
  		SDL_RenderPresent(renderer_);
          	break;
          }
      }
      if (input_manager_->press_key_p(player_type::p1, input_device::h)
      	  || input_manager_->press_key_p(player_type::p2, input_device::h)){
      	  if (game_mode_!=game_mode::help){
      	  	//++game_count_;
      	  	game_mode_=game_mode::help;
      	  }
      	  }
      if (input_manager_->press_key_p(player_type::p1, input_device::q)
      	  || input_manager_->press_key_p(player_type::p2, input_device::q)){
      	  if (game_mode_==game_mode::help){
      	  	//++game_count_;
      	  	game_mode_=game_mode::single;
      	  }
      	  }

      if (input_manager_->press_key_p(player_type::p1, input_device::x)
          || input_manager_->press_key_p(player_type::p2, input_device::x)
          || input_manager_->press_key_p(player_type::p1, input_device::space)
          || input_manager_->press_key_p(player_type::p2, input_device::space)) {
        wipe_->set_wipe_out();
        wipe_->draw(screen::width);
        ++game_count_;
      }

      if (input_manager_->press_key_p(player_type::p1, input_device::button_2)
          || input_manager_->press_key_p(player_type::p2, input_device::button_2)) {
        game_count_ -= 2;
        game_mode_ = game_mode::single;
      }

      if (input_manager_->press_key_p(player_type::p1, input_device::down)
          || input_manager_->press_key_p(player_type::p2, input_device::down)) {
        game_mode_ = game_mode::battle;
      } else if (input_manager_->press_key_p(player_type::p1, input_device::up)
                 || input_manager_->press_key_p(player_type::p2,
                                                input_device::up)) {
        game_mode_ = game_mode::single;
      }
      break;
    }
    case 5: {
      switch (game_mode_) {
        case game_mode::single: {
          SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
          SDL_RenderFillRect(renderer_, &p1_str_dst);
          draw_text(font_size::x16, rgb::white, p1_mode_pos, p1_mode_str);
          draw_text(font_size::x16, rgb::black, vs_mode_pos, vs_mode_str);
          draw_text(font_size::x16, rgb::black, hp_mode_pos, hp_mode_str);
          break;
        }
        case game_mode::battle: {
          SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
          SDL_RenderFillRect(renderer_, &vs_str_dst);
          draw_text(font_size::x16, rgb::black, p1_mode_pos, p1_mode_str);
          draw_text(font_size::x16, rgb::white, vs_mode_pos, vs_mode_str);
          draw_text(font_size::x16, rgb::black, hp_mode_pos, hp_mode_str);
          break;
        }
        case game_mode::help: {
          SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
          SDL_RenderFillRect(renderer_, &vs_str_dst);
          draw_text(font_size::x16, rgb::black, p1_mode_pos, p1_mode_str);
          draw_text(font_size::x16, rgb::black, vs_mode_pos, vs_mode_str);
          draw_text(font_size::x16, rgb::white, hp_mode_pos, hp_mode_str);
          break;
        }
      }

      wipe_->draw(screen::width);

      // initialize globals
      if (wipe_->update()) {
        map_->init(game_mode_);
        food_->init(*map_);
        enemy_->init();
        p1_->init_pos();
        p2_->init_pos();
        p1_->set_life(2);
        p2_->set_life(2);
        p1_->set_score(0);
        p2_->set_score(0);
        p1_->set_damaged(false);
        p2_->set_damaged(false);
        p1_->set_power_mode(0);
        p2_->set_power_mode(0);

        game_count_ = 0;
        game_state_ = game_state::start;
        game_level_ = 1;

        srand((unsigned int)time(nullptr));

        Mix_PlayMusic(mixer_manager_->get_music(), -1);
      }
      break;
    }
    default:
      // NOTREACHED
      break;
  }
  IMG_Quit();
}

void Mario::game_start() noexcept {
  map_->draw(game_level_);
  food_->draw();
  enemy_->draw();
  p1_->draw(game_mode_);
  p2_->draw(game_mode_);
  draw_score();
  switch (game_count_) {
    case 0: {
      
      if (p1_->get_life() == 2 && p2_->get_life() == 2) {
        Mix_PlayChannel(se_type::beginning,
                        mixer_manager_->get_se(se_type::beginning),
                        0);
      }
      wipe_->set_wipe_in();
      wipe_->draw(screen::offset_x);
      ++game_count_;
      break;
    }
    case 1: {
      wipe_->draw(screen::offset_x);
      if (wipe_->update()) {
        ++game_count_;
      }
      break;
    }
    default:
      ++game_count_;
      break;
  }
  if (game_count_ < 130) {
    std::stringstream ss;
    ss << "LEVEL " << game_level_;
    draw_text(font_size::x36, rgb::red, Point{153, 170}, ss.str().c_str());
  } else if (game_count_ < 200) {
    draw_text(font_size::x36, rgb::red, Point{165, 170}, "START!");
  }

  if (game_count_ > 220) {
    game_count_ = 0;
    game_state_ = game_state::playing;
    p1_->set_power_mode(0);
    p2_->set_power_mode(0);
  }
  if(game_state_==game_state::playing && game_mode_==game_mode::battle)createClient();
}


void Mario::sendPacket(ENetPeer* server){
	char c[80];
	sprintf(c,"%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i",
		p1_->get_pos().x,
		p1_->get_pos().y,
		p1_->get_block().x,
		p1_->get_block().y,
		p1_->getnext_block().x,
		p1_->getnext_block().y,
		p1_->get_dir(),
		p1_->get_life(),
		p1_->get_score(),
		p1_->get_damaged(),
		p1_->get_power_mode(),
		p1_->get_anim(),
		p1_->get_animw());
		
	ENetPacket * packet = enet_packet_create (c, 
                                          strlen (c) + 1, 
                                          ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send (server, 0, packet);
}

void Mario::setP2(ENetEvent event){
	/*printf("A packet of length %lu containing %s was received from %p on channel %u.\n",
                        event.packet->dataLength,
                        event.packet->data,
                        event.peer->data,
                        event.channelID);*/
	char* str;
	cout<<event.packet->data<<"\n";
	//int l=event.packet->dataLength;
	//sprintf(str,"%s",event.packet->data);
	//string s(str);
	//cout<<str<<"\n";
	int l=event.packet->dataLength;
	int i=0;
	int j=0;
	int n=0;
	int arr[13];
	string s="";
	while(i<l-1 && n<13){
		if (event.packet->data[i]==','){
			arr[n]=stoi(s);
			n++;
			j=i+1;
			s="";
			i++;
		}
		s=s+char(event.packet->data[i]);
		i++;
	}
	i=0;
	arr[12]=stoi(s);
	Point* p= new Point();
	p->setx(arr[0]);
	p->sety(arr[1]);
	Point pp=*p;
	p2_->set_pos(pp);
	p= new Point();
	p->setx(arr[2]);
	p->sety(arr[3]);
	pp=*p;
	p2_->set_block(pp);
	p= new Point();
	p->setx(arr[4]);
	p->sety(arr[5]);
	pp=*p;
	p2_->setnext_block(pp);
	p2_->set_dir(arr[6]);
	p2_->set_life(arr[7]);
	p2_->set_score(arr[8]);
	p2_->set_damaged(arr[9]);
	p2_->set_power_mode(arr[10]);
	p2_->set_anim(arr[11]);
	p2_->set_animw(arr[12]);
	
}


void Mario::play_game() noexcept {
  if (game_mode_==game_mode::single){
  map_->draw(game_level_);
  food_->draw();
  enemy_->draw();
  p1_->draw(game_mode_);
  p2_->draw(game_mode_);
  draw_score();
  enemy_->move(debug_lose_enemy_, *map_, *p1_, *p2_);
  p1_->move(*map_, game_mode_);
  p2_->move(*map_, game_mode_);
  if (p1_->get_power_mode()) {
    p1_->set_power_mode(p1_->get_power_mode() - 1);
  }
  if (p2_->get_power_mode()) {
    p2_->set_power_mode(p2_->get_power_mode() - 1);
  }

  const bool food_state =
      food_->check_state(game_mode_, *p1_, *p2_);
  const bool hit_enemy = enemy_->check_hit_enemy(game_mode_, *p1_, *p2_);
  if (food_state) {
    game_state_ = game_state::clear;
  } else if (hit_enemy) {
    game_state_ = game_state::miss;
  }

  if (input_manager_->edge_key_p(player_type::p1, input_device::space)) {
    game_state_ = game_state::pause;
  }

  if (input_manager_->edge_key_p(player_type::p1, input_device::b)) {
    debug_lose_enemy_ = !debug_lose_enemy_;
  }
  }
  else{
  ENetEvent event;
  if (!waiting){
  SDL_Surface * image=IMG_Load("resources/graphics/connec-lost.png");
  if (image==NULL){
  std::cerr<<"unable to load image";
  }
  SDL_Texture * texture=SDL_CreateTextureFromSurface(renderer_,image);
  SDL_RenderCopy(renderer_, texture, NULL, NULL);
  SDL_RenderPresent(renderer_);
  if (input_manager_->edge_key_p(player_type::p1, input_device::space)) {
    game_state_ = game_state::title;
  }
  while (enet_host_service(Mario::client, & event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:{
                        //int l=event.packet->dataLength;
                        //enet_uint8* c=event.packet->data;
                        if (event.packet->dataLength<=2){
                        	waiting=false;
                        	enet_packet_destroy(event.packet);
                        	}
                        	
                        else{
                        waiting=true;
                        //setP2(event);
                        enet_packet_destroy(event.packet);
                        }
                        //sendPacket(event.peer);
                        /*printf("A packet of length %lu containing %s was received from %p on channel %u.\n",
                        event.packet->dataLength,
                        event.packet->data,
                        event.peer->data,
                        event.channelID);*/
                /* Clean up the packet now that we're done using it. */
                break;
                }
        }
        
   }
  }
  if (waiting){ 
  map_->draw(game_level_);
  food_->draw();
  enemy_->draw();
  p1_->draw(game_mode_);
  p2_->draw(game_mode_);
  draw_score();
  enemy_->move(debug_lose_enemy_, *map_, *p1_, *p2_);
  sendPacket(peer);
  while (enet_host_service(Mario::client, & event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:{
                        //int l=event.packet->dataLength;
                        //enet_uint8* c=event.packet->data;
                        if (event.packet->dataLength<=2){
                        	waiting=false;
                        	enet_packet_destroy(event.packet);
                        }
                        else{
                        waiting=true;
                        setP2(event);
                        enet_packet_destroy(event.packet);
                        }
                        //sendPacket(event.peer);
                        /*printf("A packet of length %lu containing %s was received from %p on channel %u.\n",
                        event.packet->dataLength,
                        event.packet->data,
                        event.peer->data,
                        event.channelID);*/
                /* Clean up the packet now that we're done using it. */
                break;
                }
        }
        
   }
  p1_->move(*map_, game_mode_);
  p2_->move(*map_, game_mode_);
  if (p1_->get_power_mode()) {
    p1_->set_power_mode(p1_->get_power_mode() - 1);
  }
  /*if (p2_->get_power_mode()) {
    p2_->set_power_mode(p2_->get_power_mode() - 1);
  }*/

  const bool food_state =
      food_->check_state(game_mode_, *p1_, *p2_);
  const bool hit_enemy = enemy_->check_hit_enemy(game_mode_, *p1_, *p2_);
  if (food_state) {
    game_state_ = game_state::clear;
  } else if (hit_enemy) {
    game_state_ = game_state::miss;
  }

  /*if (input_manager_->edge_key_p(player_type::p1, input_device::space)) {
    game_state_ = game_state::pause;
  }*/

  if (input_manager_->edge_key_p(player_type::p1, input_device::b)) {
    debug_lose_enemy_ = !debug_lose_enemy_;
  }
  }
  if (game_state_!=game_state::playing && game_mode_==game_mode::battle){closeClient();waiting=false;}
  }
}

void Mario::game_clear() noexcept {
  map_->draw(game_level_);
  food_->draw();
  enemy_->draw();
  p1_->draw(game_mode_);
  p2_->draw(game_mode_);
  draw_score();

  if (game_count_ == 0) {
    wipe_->set_wipe_out();
    wipe_->draw(screen::offset_x);
    ++game_count_;
    return;
  }

  wipe_->draw(screen::offset_x);
  if (wipe_->update()) {
    if (game_level_ >= 256) {
      game_count_ = 0;
      game_state_ = game_state::gameover;
    } else {
      game_count_ = 0;
      game_state_ = game_state::start;
      ++game_level_;
      food_->init(*map_);
      enemy_->init();
      p1_->init_pos();
      p2_->init_pos();
    }
  }
}

void Mario::game_miss() noexcept {
  map_->draw(game_level_);
  food_->draw();
  enemy_->draw();
  p1_->draw(game_mode_);
  p2_->draw(game_mode_);
  draw_score();

  if (game_count_ == 0) {
    Mix_HaltChannel(-1);
    Mix_PlayChannel(-1, mixer_manager_->get_se(se_type::death), 0);
    wipe_->set_wipe_out();
    if (p1_->get_life() == 0 || p2_->get_life() == 0) {
      wipe_->draw(screen::width);
    } else {
      wipe_->draw(screen::offset_x);
    }
    ++game_count_;
    return;
  }

  if (p1_->get_life() == 0 || p2_->get_life() == 0) {
    wipe_->draw(screen::width);
  } else {
    wipe_->draw(screen::offset_x);
  }

  Player *p = p1_->get_damaged() ? p1_.get() : p2_.get();
  const Point pos = p->get_pos();
  p->set_pos(Point{pos.x, pos.y - 1});
  if (wipe_->update()) {
    const int life = p->get_life() - 1;
    p->set_life(life);
    if (life >= 0) {
      game_count_ = 0;
      game_state_ = game_state::start;
      enemy_->init();
      p1_->init_pos();
      p2_->init_pos();
      p1_->set_damaged(false);
      p2_->set_damaged(false);
    } else {
      game_count_ = 0;
      blink_count_ = 0;
      game_state_ = game_state::gameover;
    }
  }
}

void Mario::game_over() noexcept {

  const Point gameover_pos = Point{165, 100};
  const char *gameover_str = "Game Over!";
  switch (game_mode_) {
    case game_mode::single: {
      //SDL_SetRenderDrawColor(renderer_, 18, 187, 224, 0);
      //SDL_RenderClear(renderer_);
      switch (game_count_) {
        case 0: {
          draw_text(font_size::x36, rgb::red, gameover_pos, gameover_str);
          wipe_->set_wipe_in();
          wipe_->draw(screen::width);
          ++game_count_;
          break;
        }
        case 1: {
          draw_text(font_size::x36, rgb::red, gameover_pos, gameover_str);
          wipe_->draw(screen::width);
          if (wipe_->update()) {
            ++game_count_;
          }
          break;
        }
        case 2: {
          SDL_Surface * image=IMG_Load("resources/graphics/mario-lost.png");
            if (image==NULL){
  			std::cerr<<"unable to load image";
  		}
  		SDL_Texture * texture=SDL_CreateTextureFromSurface(renderer_,image);
  		SDL_RenderCopy(renderer_, texture, NULL, NULL);
  		SDL_RenderPresent(renderer_);
          draw_text(font_size::x36, rgb::red, gameover_pos, gameover_str);
          std::stringstream ss;
          ss << "Your Score is " << p1_->get_score();
          draw_text(font_size::x36, rgb::black, Point{120, 220},
                    ss.str().c_str());

          if (blink_count_ < 30) {
            draw_text(font_size::x16, rgb::black, Point{210, 350},
                      "Press SPACE key for Menu");
            ++blink_count_;
          } else if (blink_count_ < 60) {
            ++blink_count_;
          } else {
            blink_count_ = 0;
          }

          if (input_manager_->press_key_p(player_type::p1, input_device::x)
              || input_manager_->press_key_p(player_type::p2, input_device::x)
              || input_manager_->press_key_p(player_type::p1, input_device::space)) {
            ++game_count_;
            wipe_->set_wipe_out();
            wipe_->draw(screen::width);
          }
          break;
        }
        case 3: {
          wipe_->draw(screen::width);
          if (wipe_->update()) {
            blink_count_ = 0;
            game_count_ = 0;
            game_state_ = game_state::title;
            Mix_HaltMusic();
          }
          break;
        }
        default:
          // NOTREACHED
          break;
      }
      break;
    }
    case game_mode::battle: {
      SDL_SetRenderDrawColor(renderer_, 18, 187, 224, 0);
      SDL_RenderClear(renderer_);
      switch (game_count_) {
        case 0: {
          draw_text(font_size::x36, rgb::red, gameover_pos, gameover_str);
          wipe_->set_wipe_in();
          wipe_->draw(screen::width);
          ++game_count_;
          break;
        }
        case 1: {
          draw_text(font_size::x36, rgb::red, gameover_pos, gameover_str);
          wipe_->draw(screen::width);
          if (wipe_->update()) {
            ++game_count_;
          }
          break;
        }
        case 2: {
          
          draw_text(font_size::x36, rgb::red, gameover_pos, gameover_str);
          std::stringstream ss;
          const unsigned int p1_score = p1_->get_score();
          const unsigned int p2_score = p2_->get_score();
          const unsigned int l1 = p1_->get_life();
          const unsigned int l2 = p2_->get_life();
          if (l1>l2 ||(l1==l2 && p1_score > p2_score)) {
            SDL_Surface * image=IMG_Load("resources/graphics/mario-win.png");
            if (image==NULL){
  			std::cerr<<"unable to load image";
  		}
  		SDL_Texture * texture=SDL_CreateTextureFromSurface(renderer_,image);
  		SDL_RenderCopy(renderer_, texture, NULL, NULL);
  		SDL_RenderPresent(renderer_);
            ss << "Mario wins with a Score of " << p1_score;
            draw_text(font_size::x36, rgb::black, Point{170, 0},
                      ss.str().c_str());
          } else if (l1<l2 || (l1==l2 && p1_score < p2_score)) {
            SDL_Surface * image=IMG_Load("resources/graphics/mario-lost.png");
            if (image==NULL){
  			std::cerr<<"unable to load image";
  		}
  		SDL_Texture * texture=SDL_CreateTextureFromSurface(renderer_,image);
  		SDL_RenderCopy(renderer_, texture, NULL, NULL);
  		SDL_RenderPresent(renderer_);
            ss << "Luigi wins with a Score of " << p2_score;
            draw_text(font_size::x36, rgb::black, Point{170, 0},
                      ss.str().c_str());
          } else {
            ss << "It's a Draw! Score is " << p1_score;
            draw_text(font_size::x36, rgb::black, Point{170, 0},
                      ss.str().c_str());
          }

          if (blink_count_ < 30) {
            draw_text(font_size::x16, rgb::black, Point{210, 380},
                      "Press SPACE key for Menu");
            ++blink_count_;
          } else if (blink_count_ < 60) {
            ++blink_count_;
          } else {
            blink_count_ = 0;
          }

          if (input_manager_->press_key_p(player_type::p1, input_device::x)
              || input_manager_->press_key_p(player_type::p2, input_device::x)
              || input_manager_->press_key_p(player_type::p1, input_device::space)) {
            ++game_count_;
            wipe_->set_wipe_out();
            wipe_->draw(screen::width);
          }
          break;
        }
        case 3: {
          wipe_->draw(screen::width);
          if (wipe_->update()) {
            blink_count_ = 0;
            game_count_ = 0;
            game_state_ = game_state::title;
          }
          break;
        }
        default:
          // NOTREACHED
          break;
      }
      break;
    }
  }
}
