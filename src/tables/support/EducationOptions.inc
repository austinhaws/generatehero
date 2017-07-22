<?php

namespace Heroes\tables\superabilities;

// when rolling education, these settings modify what the character gains
class EducationOptions
{
    /** @var  int */
    public $numberProgramsModifer;
    /** @var  array */
    public $disallowedPrograms;
    /** @var  array */
    public $disallowedSkills;

    function __construct($numberProgramsModifer, $disallowedPrograms, $disallowedSkills)
    {
        $this->numberProgramsModifer = $numberProgramsModifer;
        $this->disallowedPrograms = $disallowedPrograms;
        $this->disallowedSkills = $disallowedSkills;
    }
}