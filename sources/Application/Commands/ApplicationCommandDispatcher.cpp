#include "ApplicationCommandDispatcher.h"
#include "Application/Player/Player.h"

ApplicationCommandDispatcher::ApplicationCommandDispatcher() {
	project_=0 ;
} ;

ApplicationCommandDispatcher::~ApplicationCommandDispatcher() {
} ;

void ApplicationCommandDispatcher::Execute(FourCC id, float value) {
	switch(id) {
		case TRIG_TEMPO_TAP:
			if (value>0.5) OnTempoTap();
			break ;
		case TRIG_SEQ_QUEUE_ROW:
			if (value>0.5) OnQueueRow();
			break ;
		case TRIG_FILTER_CUTOFF_CH1:
			if (value>0.5) OnFilterCutoff(1, value);
			break ;
	}
} ;

void ApplicationCommandDispatcher::Init(Project *project) {
	project_=project;
} ;

void ApplicationCommandDispatcher::Close() {
	project_=0 ;
} ;

void ApplicationCommandDispatcher::OnTempoTap() {
	if (!project_) return ;
	project_->OnTempoTap() ;
} ;

void ApplicationCommandDispatcher::OnQueueRow() {
	if (!project_) return ;
	Player *player=Player::GetInstance() ;
    player->SetSequencerMode(SM_LIVE) ;
	player->OnSongStartButton(0,7,false,false) ;
} ;

void ApplicationCommandDispatcher::OnFilterCutoff(int channel, ushort value) {
	if (!project_) return ;
	//SampleInstrument *player=SampleInstrument::GetInstance() ;
	SampleInstrument::ProcessCommand(channel,FourCC cc,ushort value);
} ;

#define TEMPO_NUDGE 3
void ApplicationCommandDispatcher::OnNudgeDown() {
	project_->NudgeTempo(-TEMPO_NUDGE) ;
} ;

void ApplicationCommandDispatcher::OnNudgeUp() {
	project_->NudgeTempo(TEMPO_NUDGE) ;
} ;