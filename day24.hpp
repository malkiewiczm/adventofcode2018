#define immune(what)(me->immune.insert(djb_hash(what)))
#define weak(what)(me->weak.insert(djb_hash(what)))
#define attack_mode(what)(me->attack_mode = djb_hash(what))

static group_t groups_solid[30];
static group_t groups_working[30];
static group_t *groups[30];

#ifdef SAMPLE

#define GROUP_COUNT 4

static void init()
{
	trace("sample input");
	
	group_t *me = groups_solid;
	me->evil = false;
	me->n = 17;
	me->hp = 5390;
	immune("radiation");
	weak("bludge");
	me->attack_amt = 4507;
	attack_mode("fire");
	me->rank = 2;
	++me;

	me->evil = false;
	me->n = 989;
	me->hp = 1274;
	immune("fire");
	weak("bludge");
	weak("slashing");
	me->attack_amt = 25;
	attack_mode("slashing");
	me->rank = 3;
	++me;

	me->evil = true;
	me->n = 801;
	me->hp = 4706;
	weak("radiation");
	me->attack_amt = 116;
	attack_mode("bludge");
	me->rank = 1;
	++me;

	me->evil = true;
	me->n = 4485;
	me->hp = 2961;
	immune("radiation");
	weak("fire");
	weak("cold");
	me->attack_amt = 12;
	attack_mode("slashing");
	me->rank = 4;
	++me;
}

#else
#ifdef JOE

#define GROUP_COUNT 20

static void init()
{
	trace("joe input");
	group_t *me = groups_solid;

	me->evil = false;
	me->n = 357;
	me->hp = 6038;
	weak("bludgeoning");
	me->attack_amt = 166;
	attack_mode("slashing");
	me->rank = 5;
	++me;

	me->evil = false;
	me->n = 1265;
	me->hp = 3299;
	weak("cold");
	immune("radiation");
	me->attack_amt = 25;
	attack_mode("fire");
	me->rank = 3;
	++me;

	me->evil = false;
	me->n = 137;
	me->hp = 3682;
	me->attack_amt = 264;
	attack_mode("radiation");
	me->rank = 13;
	++me;

	me->evil = false;
	me->n = 5484;
	me->hp = 2545;
	immune("slashing");
	me->attack_amt = 4;
	attack_mode("bludgeoning");
	me->rank = 16;
	++me;

	me->evil = false;
	me->n = 5242;
	me->hp = 11658;
	weak("radiation");
	me->attack_amt = 19;
	attack_mode("bludgeoning");
	me->rank = 20;
	++me;

	me->evil = false;
	me->n = 3333;
	me->hp = 7277;
	weak("slashing");
	weak("bludgeoning");
	me->attack_amt = 16;
	attack_mode("slashing");
	me->rank = 4;
	++me;

	me->evil = false;
	me->n = 6136;
	me->hp = 5157;
	immune("fire");
	weak("radiation");
	me->attack_amt = 7;
	attack_mode("fire");
	me->rank = 14;
	++me;

	me->evil = false;
	me->n = 1215;
	me->hp = 2154;
	me->attack_amt = 13;
	attack_mode("bludgeoning");
	me->rank = 15;
	++me;

	me->evil = false;
	me->n = 753;
	me->hp = 3242;
	weak("slashing");
	me->attack_amt = 33;
	attack_mode("cold");
	me->rank = 6;
	++me;

	me->evil = false;
	me->n = 1325;
	me->hp = 8064;
	me->attack_amt = 58;
	attack_mode("cold");
	me->rank = 2;
	++me;

	me->evil = true;
	me->n = 812;
	me->hp = 13384;
	immune("slashing");
	weak("cold");
	me->attack_amt = 29;
	attack_mode("fire");
	me->rank = 7;
	++me;

	me->evil = true;
	me->n = 971;
	me->hp = 28820;
	immune("fire");
	me->attack_amt = 55;
	attack_mode("bludgeoning");
	me->rank = 8;
	++me;

	me->evil = true;
	me->n = 159;
	me->hp = 51016;
	weak("slashing");
	me->attack_amt = 482;
	attack_mode("radiation");
	me->rank = 11;
	++me;

	me->evil = true;
	me->n = 5813;
	me->hp = 10079;
	immune("bludgeoning");
	immune("cold");
	immune("fire");
	me->attack_amt = 2;
	attack_mode("cold");
	me->rank = 18;
	++me;

	me->evil = true;
	me->n = 708;
	me->hp = 30474;
	me->attack_amt = 76;
	attack_mode("bludgeoning");
	me->rank = 10;
	++me;

	me->evil = true;
	me->n = 874;
	me->hp = 39547;
	immune("radiation");
	immune("fire");
	immune("cold");
	me->attack_amt = 69;
	attack_mode("radiation");
	me->rank = 12;
	++me;

	me->evil = true;
	me->n = 1608;
	me->hp = 30732;
	weak("fire");
	weak("cold");
	me->attack_amt = 29;
	attack_mode("radiation");
	me->rank = 17;
	++me;

	me->evil = true;
	me->n = 6715;
	me->hp = 14476;
	weak("radiation");
	me->attack_amt = 3;
	attack_mode("bludgeoning");
	me->rank = 19;
	++me;

	me->evil = true;
	me->n = 2023;
	me->hp = 36917;
	weak("slashing");
	me->attack_amt = 36;
	attack_mode("bludgeoning");
	me->rank = 1;
	++me;

	me->evil = true;
	me->n = 1214;
	me->hp = 14587;
	immune("cold");
	me->attack_amt = 16;
	attack_mode("radiation");
	me->rank = 9;
	++me;
}

#else
#define GROUP_COUNT 20

static void init()
{
	group_t *me = groups_solid;

	me->evil = false;
	me->n = 2991;
	me->hp = 8084;
	weak("fire");
	me->attack_amt = 19;
	attack_mode("radiation");
	me->rank = 11;
	++me;

	me->evil = false;
	me->n = 4513;
	me->hp = 3901;
	weak("slashing");
	immune("bludgeoning");
	immune("radiation");
	me->attack_amt = 7;
	attack_mode("bludgeoning");
	me->rank = 12;
	++me;

	me->evil = false;
	me->n = 5007;
	me->hp = 9502;
	immune("bludgeoning");
	weak("fire");
	me->attack_amt = 16;
	attack_mode("fire");
	me->rank = 2;
	++me;

	me->evil = false;
	me->n = 2007;
	me->hp = 5188;
	weak("radiation");
	me->attack_amt = 23;
	attack_mode("cold");
	me->rank = 9;
	++me;

	me->evil = false;
	me->n = 1680;
	me->hp = 1873;
	immune("bludgeoning");
	weak("radiation");
	me->attack_amt = 10;
	attack_mode("bludgeoning");
	me->rank = 10;
	++me;

	me->evil = false;
	me->n = 1344;
	me->hp = 9093;
	immune("bludgeoning");
	immune("cold");
	weak("radiation");
	me->attack_amt = 63;
	attack_mode("cold");
	me->rank = 16;
	++me;

	me->evil = false;
	me->n = 498;
	me->hp = 2425;
	immune("fire");
	immune("bludgeoning");
	immune("cold");
	me->attack_amt = 44;
	attack_mode("slashing");
	me->rank = 3;
	++me;

	me->evil = false;
	me->n = 1166;
	me->hp = 7295;
	me->attack_amt = 56;
	attack_mode("bludgeoning");
	me->rank = 8;
	++me;

	me->evil = false;
	me->n = 613;
	me->hp = 13254;
	immune("radiation");
	immune("cold");
	immune("fire");
	me->attack_amt = 162;
	attack_mode("radiation");
	me->rank = 15;
	++me;

	me->evil = false;
	me->n = 1431;
	me->hp = 2848;
	weak("radiation");
	me->attack_amt = 19;
	attack_mode("cold");
	me->rank = 1;
	++me;

	me->evil = true;
	me->n = 700;
	me->hp = 47055;
	weak("fire");
	immune("slashing");
	me->attack_amt = 116;
	attack_mode("fire");
	me->rank = 14;
	++me;

	me->evil = true;
	me->n = 2654;
	me->hp = 13093;
	weak("radiation");
	me->attack_amt = 8;
	attack_mode("radiation");
	me->rank = 19;
	++me;

	me->evil = true;
	me->n = 5513;
	me->hp = 18026;
	immune("radiation");
	weak("slashing");
	me->attack_amt = 6;
	attack_mode("slashing");
	me->rank = 20;
	++me;

	me->evil = true;
	me->n = 89;
	me->hp = 48412;
	weak("cold");
	me->attack_amt = 815;
	attack_mode("radiation");
	me->rank = 17;
	++me;

	me->evil = true;
	me->n = 2995;
	me->hp = 51205;
	weak("cold");
	me->attack_amt = 28;
	attack_mode("slashing");
	me->rank = 7;
	++me;

	me->evil = true;
	me->n = 495;
	me->hp = 21912;
	me->attack_amt = 82;
	attack_mode("cold");
	me->rank = 13;
	++me;

	me->evil = true;
	me->n = 2911;
	me->hp = 13547;
	me->attack_amt = 7;
	attack_mode("slashing");
	me->rank = 18;
	++me;

	me->evil = true;
	me->n = 1017;
	me->hp = 28427;
	immune("fire");
	me->attack_amt = 52;
	attack_mode("fire");
	me->rank = 4;
	++me;

	me->evil = true;
	me->n = 2048;
	me->hp = 29191;
	weak("bludgeoning");
	me->attack_amt = 22;
	attack_mode("bludgeoning");
	me->rank = 6;
	++me;

	me->evil = true;
	me->n = 1718;
	me->hp = 15725;
	immune("cold");
	me->attack_amt = 18;
	attack_mode("slashing");
	me->rank = 5;
	++me;
}

#endif
#endif
