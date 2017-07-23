<?php
namespace Heroes\hero;


class Psionic
{
    /** @var string title */
    public $title;
    /** @var string range */
    public $range;
    /** @var string duration */
    public $duration;
    /** @var int psionics points*/
    public $isp;
    /** @var string savingThrow */
    public $savingThrow;
    /** @var string description */
    public $description;

    public function __construct($title, $range, $duration, $isp, $savingThrow, $description)
    {
        $this->title = $title;
        $this->range = $range;
        $this->duration = $duration;
        $this->isp = $isp;
        $this->savingThrow = $savingThrow;
        $this->description = $description;
    }


}