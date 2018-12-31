#ifndef UTIL_FDE_SELECT_H
#define UTIL_FDE_SELECT_H

Fdevents::Fdevents(){
	maxfd = -1;
	FD_ZERO(&readset);
	FD_ZERO(&writeset);
}

Fdevents::~Fdevents(){
	for(size_t i= 0; i<events.size(); i++){
		delete events[i];
	}
	events.clear();
	ready_events.clear();
}

bool Fdevents::isset(int fd, int flag){
	struct Fdevent *fde = get_fde(fd);
	return (bool)(fde->s_flags & flag);
}

int Fdevent::set(int fd, int flags, int data_num, void *data_ptr){
	if(fd > FD_SETSIZE - 1){
		return -1;
	}

	struct Fdevent *fde = get_fde(fd);
	if(fde->s_flags & flag){
		return 0;
	}

	if(flags & FDEVENT_IN) FD_SET(fd, &readset);
	if(flags & FDEVENT_OUT) FD_SET(fd, &writeset);

	fde->data.num = data_num;
	fde->data.ptr = data_ptr;
	fde->s_flags |= flags;
	maxfd = fd > maxfd? fd : maxfd;

	return 0;
}

int Fdevent::del(int fd){
	FD_CLR(fd, &readset);
	FD_CLR(fd, &writeset);

	struct Fdevent *fde = get_fde(fd);
	fde->s_flags = FDEVENT_NONE;
	while(maxfd >= 0 && this->events[maxfd]->s_flags == 0){
		maxfd --;
	}
	return 0;
}

int Fdevent::clr(int fd, int flags){
	struct Fdevent *fde = get_fde(fd);
	if(!(fde->s_flags & flags)){
		return 0;
	}

	if(flags & FDEVENT_IN) FD_CLR(fd, &readset);
	if(flags & FDEVENT_OUT) FD_CLR(fd, &writeset);

	fde->s_flags &= ~flags;
	while(this->events[maxfd]->s_flags == 0){
		maxfd --;
	}
	return 0;
}

