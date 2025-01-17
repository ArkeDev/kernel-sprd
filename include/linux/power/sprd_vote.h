/*
 * Copyright (C) 2011 Unisoc Co., Ltd.
 * Jinfeng.lin <Jinfeng.Lin1@unisoc.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
**/

#ifndef _SPRD_VOTE_H
#define _SPRD_VOTE_H

#include <linux/mutex.h>

enum SPRD_VOTE_TYPE {
	SPRD_VOTE_TYPE_UNKNOWN,
	SPRD_VOTE_TYPE_IBAT,
	SPRD_VOTE_TYPE_IBUS,
	SPRD_VOTE_TYPE_CCCV,
	SPRD_VOTE_TYPE_ALL,
	SPRD_VOTE_TYPE_MAX,
};

enum SPRD_VOTE_CMD {
	SPRD_VOTE_CMD_UNKNOWN,
	SPRD_VOTE_CMD_MIN,
	SPRD_VOTE_CMD_MAX,
	SPRD_VOTE_CMD_ALL,
};

enum SPRD_VOTE_TYPE_IBAT_ID {
	SPRD_VOTE_TYPE_IBAT_ID_JEITA,
	SPRD_VOTE_TYPE_IBAT_ID_CHARGER_TYPE,
	SPRD_VOTE_TYPE_IBAT_ID_CONSTANT_CHARGE_CURRENT,
	SPRD_VOTE_TYPE_IBAT_ID_MAX,
};

enum SPRD_VOTE_TYPE_IBUS_ID {
	SPRD_VOTE_TYPE_IBUS_ID_INPUT_CURRENT_LIMIT,
	SPRD_VOTE_TYPE_IBUS_ID_CHARGE_CONTROL_LIMIT,
	SPRD_VOTE_TYPE_IBUS_ID_CHARGER_TYPE,
	SPRD_VOTE_TYPE_IBUS_ID_MAX,
};

enum SPRD_VOTE_TYPE_CCCV_ID {
	SPRD_VOTE_TYPE_CCCV_ID_JEITA,
	SPRD_VOTE_TYPE_CCCV_ID_IR,
	SPRD_VOTE_TYPE_CCCV_ID_MAX,
};

static const char * const vote_type_names[] = {
	[SPRD_VOTE_TYPE_UNKNOWN] = "VOTE_TYPE_UNKNOWN",
	[SPRD_VOTE_TYPE_IBAT] = "VOTE_TYPE_IBAT",
	[SPRD_VOTE_TYPE_IBUS] = "VOTE_TYPE_IBUS",
	[SPRD_VOTE_TYPE_CCCV] = "VOTE_TYPE_CCCV",
	[SPRD_VOTE_TYPE_ALL] = "VOTE_TYPE_ALL",
};

static const char * const vote_cmd_names[] = {
	[SPRD_VOTE_CMD_UNKNOWN] = "VOTE_CMD_UNKNOWN",
	[SPRD_VOTE_CMD_MAX] = "VOTE_CMD_MAX",
	[SPRD_VOTE_CMD_MIN] = "VOTE_CMD_MIN",
	[SPRD_VOTE_CMD_ALL] = "VOTE_CMD_ALL",
};

typedef struct sprd_vote_client {
	int value;
	int enable;
} sprd_vote_client;

struct sprd_vote {
	const char *name;
	struct mutex lock;
	sprd_vote_client ibat_client[SPRD_VOTE_TYPE_IBAT_ID_MAX];
	sprd_vote_client ibus_client[SPRD_VOTE_TYPE_IBUS_ID_MAX];
	sprd_vote_client cccv_client[SPRD_VOTE_TYPE_CCCV_ID_MAX];
	int (*vote)(struct sprd_vote *vote_gov, bool enable, int vote_type,
		    int vote_type_id, int vote_cmd, int value, void *data);
	void (*cb)(struct sprd_vote *vote_gov, int vote_type, int value, void *date);
	void (*destroy)(struct sprd_vote *vote_gov);
	void *data;
};

struct sprd_vote *sprd_charge_vote_register(char *name,
					    void (*cb)(struct sprd_vote *vote_gov,
						       int vote_type, int value,
						       void *data),
					    void *data);
 #endif /* _SPRD_VOTE_H */

