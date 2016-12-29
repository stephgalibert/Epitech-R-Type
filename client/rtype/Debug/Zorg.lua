function getTarget(mobPosX, mobPosY, p0PosX, p0PosY, p1PosX, p1PosY, p2PosX, p2PosY, p3PosX, p3PosY)
	posArray =  {
		{p0PosX, p0PosY},
		{p1PosX, p1PosY},
		{p2PosX, p2PosY},
		{p3PosX, p3PosY}
	}
	indexToRet = 10
	nearestTarget = math.abs(mobPosX - p0PosX) + math.abs(mobPosY - p0PosY)
	for i, v in ipairs(posArray) do
		if v[1] ~= -1 and v[2] ~= -1 then
			tmp = math.abs(mobPosX - v[1]) + math.abs(mobPosY - v[2])
			if tmp < nearestTarget then
				nearestTarget = tmp
				indexToRet = i
			end
		end
	end
	return (indexToRet - 1);
end	