<?php
namespace Heroes\hero\insanity;

class Insanity
{
    /** @var string type of the insanity */
    public $type;
    /** @var string description */
    public $description;

    function __construct($type, $description)
    {
        $this->type = $type;
        $this->description = $description;
    }

}