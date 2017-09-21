Cards["Petrova, Channeler of Suns"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Aqua Master"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Stallob, the Lifequasher"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Magmadragon Ogrist Vhal"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Stratosphere Giant"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 3,

	HandleMessage = function(id) --test
		local check = function(cid,sid)
			if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_HAND and getCardType(sid)==TYPE_CREATURE) then
				return 1
			else
				return 0
			end
		end

		local func = function(id)
			local ch = createChoice("Choose a creature in your hand", 0, id, getOpponent(getCardOwner(id)), check)
			if(ch>=0) then
				moveCard(ch, ZONE_BATTLE)

				local ch2 = createChoice("Choose a creature in your hand", 0, id, getOpponent(getCardOwner(id)), check)
				if(ch2>=0) then
					moveCard(ch2, ZONE_BATTLE)
				end
			end
		end

		Abils.onSummon(id, func)
	end
}

Cards["Glena Vuele, the Hypnotic"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Marching Motherboard"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Azaghast, Tyrant of Shadows"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Balesk Baj, the Timeburner"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Vreemah, Freaky Mojo Totem"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Betrale, the Explorer"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.untapAtEOT(id)
		Abils.cantAttackPlayers(id)
	end
}

Cards["Cosmic Wing"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local mod = function(cid,mid)
            Abils.cantBeBlocked(cid)
	        Abils.destroyModAtEOT(cid,mid)
        end
		local ch = createChoice("Choose creature",0,id,getCardOwner(id),Checks.InYourBattle)
		if(ch>=0) then
            createModifier(ch,mod)
        end
        Functions.EndSpell(id)
	end
}

Cards["Cyclolink, Spectral Knight"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Jil Warka, Time Guardian"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Kalute, Vizier of Eternity"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Micute, the Oracle"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Mihail, Celestial Elemental"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Nexus Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Tra Rion, Penumbra Guardian"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Unified Resistance"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Abduction Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Emperor Maroll"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Hokira"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Impossible Tunnel"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Kelp Candle"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Scout Cluster"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Submarine Project"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Tekorax"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Tentacle Cluster"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Zeppelin Crawler"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Acid Reflux, the Fleshboiler"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)
		Abils.Slayer(id)
	end
}

Cards["Bat Doctor, Shadow of Undeath"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Gabzagul, Warlord of Pain"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Grinning Hunger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Ice Vapor, Shadow of Anguish"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Necrodragon Izorist Vhal"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Slash Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Trixo, Wicked Doll"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Venom Worm"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Zombie Carnival"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Aerodactyl Kooza"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Blizzard of Spears"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Fists of Forever"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Gigio's Hammer"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Quakesaur"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Relentless Blitz"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Shock Trooper Mykee"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Simian Warrior Grash"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Snaptongue Lizard"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Steam Rumbler Kain"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Cavern Raider"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Dance of the Sproutlings"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Mana Bonanza"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Silvermoon Trailblazer"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Solid Horn"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.manaAfterDestroyed(id)
	end
}

Cards["Storm Wrangler, the Furious"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Terradragon Anrist Vhal"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Vine Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Whip Scorpion"] = {
	shieldtrigger = 1,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,3000)
	end
}

Cards["Whispering Totem"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

