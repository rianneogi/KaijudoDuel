Cards["Nastasha, Channeler of Suns"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Emperor Quazla"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Super Necrodragon Abzo Dolba"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Uberdragon Bajula"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 3,

	HandleMessage = function(id)
		Abils.Evolution(id,"Armoured Dragon")
		Abils.destroyOppManaOnAttack(id,2)
	end
}

Cards["Super Terradragon Bailas Gale"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Kuukai, Finder of Karma"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Aqua Ranger"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantBeBlocked(id)
		Abils.returnAfterDestroyed(id)
	end
}

Cards["Megaria, Empress of Dread"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Magmadragon Jagalzor"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Kachua, Keeper of the Icegate"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Dracobarrier"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Laser Whip"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Lunar Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Migalo, Vizier of Spycraft"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Misha, Channeler of Suns"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Nariel, the Oracle"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Sasha, Channeler of Suns"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Sol Galla, Halo Guardian"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Solar Grass"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Thrumiss, Zephyr Guardian"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Aqua Grappler"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Candy Cluster"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Eureka Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		drawCards(getCardOwner(id),1)
	end,
	
	HandleMessage = function(id)
		Abils.Charger(id)
	end
}

Cards["Grape Globbo"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Illusion Fish"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Lalicious"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Marine Scramble"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Prowling Elephish"] = {
	shieldtrigger = 0,
	blocker = 1,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Vikorakys"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Wave Lance"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local ch = createChoice("Choose a creature",0,id,getCardOwner(id),Checks.InBattle)
	    if(ch>=0) then
            moveCard(ch,ZONE_HAND)

			if(isCreatureOfRace(ch, "Dragon")==1) then
				drawCards(getCardOwner(id), 1)
			end
        end
        Functions.EndSpell(id)
	end
}

Cards["Corpse Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Skeleton Vice"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Dimension Splitter"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Gachack, Mechanical Doll"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Gigaclaws"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Motorcycle Mutant"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Necrodragon Galbazeek"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Necrodragon Giland"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Scream Slicer, Shadow of Fear"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Tyrant Worm"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Bruiser Dragon"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Furious Onslaught"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Kyrstron, Lair Delver"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Magmadragon Melgars"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Missile Soldier Ultimo"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Rocketdive Skyterror"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantBeAttacked(id)
		Abils.cantAttackPlayers(id)
		Abils.PowerAttacker(id,1000)
	end
}

Cards["Slaphappy Soldier Galback"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Torpedo Skyterror"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Totto Pipicchi"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Volcano Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local valid = function(cid,sid)
            if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCreaturePower(sid)<=2000) then
		        return 1
	        else
		        return 0
	        end
        end
        local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),valid)
	    if(ch>=0) then
            destroyCreature(ch)
        end
        Functions.EndSpell(id)
	end,

	HandleMessage = function(id)
		Abils.Charger(id)
	end
}

Cards["Bakkra Horn, the Silent"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Carbonite Scarab"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Coliseum Shell"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Dracodance Totem"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Muscle Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id)
		local mod = function(cid,mid)
            Abils.bonusPower(cid,3000)
		    Abils.destroyModAtEOT(cid,mid)
        end
        local func = function(cid,sid)
            createModifier(sid,mod)
        end
		Functions.executeForCreaturesInBattle(id,getCardOwner(id),func)
        Functions.EndSpell(id)
	end,

	HandleMessage = function(id)
		Abils.Charger(id)
	end
}

Cards["Quixotic Hero Swine Snout"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Root Charger"] = {
	shieldtrigger = 0,

	OnCast = function(id) --todo
	end
}

Cards["Senia, Orchard Avenger"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Terradragon Gamiratar"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 1,

	HandleMessage = function(id) --todo
	end
}

Cards["Terradragon Regarion"] = {
	shieldtrigger = 0,
	blocker = 0,
	breaker = 2,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,3000)
	end
}

